/* 1. SOTIRIOS-ELEFTHERIOS DIMITROUSIS | AM: 2022202100048 | email: dit21048@go.uop.gr
 * 2. ATHANASIOS DOUROS | AM: 2022202200236 | email: dit22236@go.uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int x;
    int y;
    int type;
}mark_coords;

void printmine(int** mine, int m, int n);
void cheat(int x, int y, int** mine, char ch[50]);
void mark(int count, int x, int y, int** mine, int n, int m, char ch[50], mark_coords** mc);
void unmark(int count, int x, int y, int** mine, int n, int m, char ch[50], mark_coords** mc);
void open(int x, int y, int n, int m, int** mine, char ch[50]);
void init(int i ,int j, int k, int n, int m, int x, int y, int** mine, int num_mines, int choice, char ch[50]);

int main() {

//Dhlwsh pinaka kai aparaititwn metablhtwn

    int **mine, m, n, i, j, k, max_n, max_m, num_mines, choice, x,y, unopened_counter = 0, count = 0;
    char ch[50];
    mark_coords **mc;


    printf("Give the size of the columns\n");
    scanf("%d", &m);
    while (m < 8) {
        printf("Minimum size is 8 columns\n");
        scanf("%d", &m);
    }
    while (m > 40) {
        printf("Maximum size is 40 columns\n");
        scanf("%d", &m);
    }
    printf("Give the size of the lines\n");
    scanf("%d", &n);
    while (n < 8) {
        printf("Minimum size is 8 lines\n");
        scanf("%d", &n);
    }
    while (n > 40) {
        printf("Maximum size is 40 lines\n");
        scanf("%d", &n);
    }
    mine = (int **) malloc(m * sizeof(int *));
    if (mine == NULL) {
        printf("Error! No memory allocated.\n");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        mine[i] = (int *) malloc(n * sizeof(int));
        if (mine[i] == NULL) {
            printf("Error! No memory allocated.\n");
            exit(1);
        }
    }

    //epilogh dyskolias

    printf("Select difficulty\n1. Easy (Mine density is 10%)\n2. Medium (Mine density is 15%)\n3. Hard (Mine density is 20%)\n4. Impossible (Mine density is 25%)\nEnter choice: ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 4) {
        printf("Not a valid choice\nEnter choice: ");
        scanf("%d", &choice);
    }

    srand(time(NULL));

    init(i,j,k,n,m,x,y,mine,num_mines, choice, ch);

    mc = (mark_coords**) malloc((n*m) * sizeof(mark_coords));
    if(mc == NULL) {
        printf("Error! No memory allocated.\n");
        exit(1);
    }
    for (count = 0; count < n; count++) {
        mc[count] = (mark_coords*) malloc((n*m) * sizeof(mark_coords));
        if (mine[count] == NULL) {
            printf("Error! No memory allocated.\n");
            exit(1);
        }
    }

   while(true) {
       printf("Select an option\n1. open(x,y)\n2. mark(x,y)\n3. cheat(x,y)\n4. unmark(x,y)\n5. Exit\n6. Print\nMake a selection\n");
       fgets(ch, 50, stdin);
       if (sscanf(ch, "open(%d,%d)", &x, &y) == 2) {
           x--;
           y--;
           if(mine[x][y] >= 0 && mine[x][y] <= 8){
               printf("This square has already been opened\n");
           }
           open(x, y, n, m, mine, ch);

           if(mine[x][y] == 10){
               printf("A mine has been hit. You lose!\n");
               free(mine);
               exit(0);
           }

           unopened_counter = 0;
           for(i = 0; i<n; i++){
               for(j=0; j<n; j++){
                   if(mine[i][j] == 9){
                       unopened_counter++;
                   }
               }
           }

           printf("Unopened: %d\n", unopened_counter);

           if(unopened_counter == 0){
               printf("Congratulations! You won this round! Starting new game with larger table. \n");
               if(n <= 35) {
                   n = n + 5;
               }else{
                   n = 40 - (40 - n);
               }
               if(m <= 35) {
                   m = m + 5;
               }else{
                   m = 40 - (40 - m);
               }
               free(mine);
               free(mc);
               if(n > 40){
                   printf("One of two dimensions has reached max limits. Congratulations! You won the game! Come back for another challenge whenever you want!. \n");
                   exit(0);
               }
               if(m > 40){
                   printf("One of two dimensions has reached max limits. Congratulations! You won the game! Come back for another challenge whenever you want!. \n");
                   exit(0);
               }
               mine = (int **) malloc(m * sizeof(int *));
               if (mine == NULL) {
                   printf("Error! No memory allocated.\n");
                   exit(1);
               }
               for (i = 0; i < n; i++) {
                   mine[i] = (int *) malloc(n * sizeof(int));
                   if (mine[i] == NULL) {
                       printf("Error! No memory allocated.\n");
                       exit(1);
                   }
               }
               mc = (mark_coords**) malloc((n*m) * sizeof(mark_coords));
               if(mc == NULL) {
                   printf("Error! No memory allocated.\n");
                   exit(1);
               }
               for (count = 0; count < n; count++) {
                   mc[count] = (mark_coords*) malloc((n*m) * sizeof(mark_coords));
                   if (mine[count] == NULL) {
                       printf("Error! No memory allocated.\n");
                       exit(1);
                   }
               }
               init(i,j,k,n,m,x,y,mine,num_mines, choice, ch);
           }
           printmine(mine, m, n);
       }
       else if (sscanf(ch, "cheat(%d,%d)", &x, &y) == 2) {
           cheat(x, y, mine, ch);
       }
       else if (sscanf(ch, "unmark(%d,%d)", &x, &y) == 2) {
           unmark(count, x, y, mine, n,m, ch, mc);
           printmine(mine, m, n);
       }
       else if (sscanf(ch, "mark(%d,%d)", &x, &y) == 2) {
           mark(count, x, y, mine, n,m, ch, mc);
           printmine(mine, m, n);
       }
       else if (sscanf(ch, "%s", ch) == 1 && strcmp(ch, "Exit") == 0) {
           printf("Exiting...\n");
           free(mine);
           free(mc);
           exit(0);
       }
       else if (sscanf(ch, "%s", ch) == 1 && strcmp(ch, "Print") == 0) {
           printmine(mine, m, n);
       } else {
           printf("Invalid parameter(s). Please try again\n");
       }
   }
}

void init(int i ,int j, int k, int n, int m, int x, int y, int** mine, int num_mines, int choice, char ch[50]){
    //arxikopoihsh pinaka apothikeyshs
    switch(choice){
        case 1:
            num_mines = (int) (n * m * 0.10);
            break;
        case 2:
            num_mines = (int) (n * m * 0.15);
            break;
        case 3:
            num_mines = (int) (n * m * 0.20);
            break;
        case 4:
            num_mines = (int) (n * m * 0.25);
            break;
    }

    //topothetisi narkwn

    for(k = 0; k<num_mines; k++) {
        i = rand() % n;
        j = rand() % m;
        if (mine[i][j] == 10){
            i = rand() % n;
            j = rand() % m;
            mine[i][j] = 10;
        }
        if (mine[i][j] == 0){
            i = rand() % n;
            j = rand() % m;
        }
        mine[i][j] = 10;
    }
    for(i = 0; i<n; i++) {
        for (j = 0; j < m; j++) {
            if (mine[i][j] != 10) {
                mine[i][j] = 9;
            }
            if (mine[i][j] == 0){
                mine[i][j] = 0;
            }
        }
    }

    //enarksi ypodoxhs apo to xrhsth

    printf("Start the game by opening a tile. Please type 'open(x,y)', where x is the line number and y is the row number.\n");
    getchar();
    fgets(ch, 50, stdin);
    if(sscanf(ch, "open(%d,%d)", &x, &y) == 2){
        while(mine[x-1][y-1] == 10) {
            for (i = 0; i < n; i++) {
                for (j = 0; j < m; j++) {
                    mine[i][j] = 9;
                }
            }
            for (k = 0; k < num_mines; k++) {
                i = rand() % n;
                j = rand() % m;
                if (mine[i][j] == 10) {
                    i = rand() % n;
                    j = rand() % m;
                    mine[i][j] = 10;
                }
                if (mine[i][j] == 0) {
                    i = rand() % n;
                    j = rand() % m;
                }
                mine[i][j] = 10;
            }
            for (i = 0; i < n; i++) {
                for (j = 0; j < m; j++) {
                    if (mine[i][j] != 10) {
                        mine[i][j] = 9;
                    }
                    if (mine[i][j] == 0) {
                        mine[i][j] = 0;
                    }
                }
            }
        }
    }
    else{
        printf("There was an error in the prompt given. Please try again.\n");
        fgets(ch, 50, stdin);
    }


// markarisma geitonikwn tetragwnwn

    for(i = 0; i<n; i++) {
        for (j = 0; j < m; j++) {
            if (mine[i][j] == 10) {
                if (i > 0 && j > 0) {
                    if(mine[i-1][j-1] != 10) {
                        mine[i - 1][j - 1] = 11; // Top left
                    }
                }
                if (i > 0) {
                    if(mine[i-1][j] != 10) {
                        mine[i - 1][j] = 11; // Top
                    }
                }

                if (i > 0 && j < m-1) {
                    if(mine[i-1][j+1] != 10) {
                        mine[i - 1][j + 1] = 11; // Top right
                    }
                }

                if (j > 0) {
                    if(mine[i][j-1] != 10) {
                        mine[i][j - 1] = 11; // Left
                    }
                }

                if (j < m - 1) {
                    if(mine[i][j+1] != 10) {
                        mine[i][j + 1] = 11; // Right
                    }
                }

                if (i < n-1 && j > 0) {
                    if(mine[i+1][j-1] != 10) {
                        mine[i + 1][j - 1] = 11; // Bottom left
                    }
                }

                if (i < n-1) {
                    if(mine[i+1][j] != 10) {
                        mine[i + 1][j] = 11; // Bottom
                    }
                }

                if (i < n-1 && j < m-1) {
                    if(mine[i+1][j+1] != 10) {
                        mine[i + 1][j + 1] = 11; // Bottom right
                    }
                }

            }
        }
    }


    //swsth topothetisi noumerwn gyrw apo tis geitonikes narkes

    for(i = 0; i<n; i++) {
        for (j = 0; j < m; j++) {
            if (mine[i][j] == 10) {
                if (i > 0 && j > 0) {
                    if (mine[i - 1][j - 1] >= 11) {
                        mine[i - 1][j - 1] = mine[i - 1][j - 1] + 1;
                    }
                }
                if (i > 0) {
                    if (mine[i - 1][j] >= 11) {
                        mine[i - 1][j] = mine[i - 1][j] + 1;
                    }
                }
                if (i > 0 && j < m-1) {
                    if (mine[i - 1][j + 1] >= 11) {
                        mine[i - 1][j + 1] = mine[i - 1][j + 1] + 1;
                    }
                }
                if (j > 0) {
                    if (mine[i][j - 1] >= 11) {
                        mine[i][j - 1] = mine[i][j - 1] + 1;
                    }
                }
                if (j < m - 1) {
                    if (mine[i][j + 1] >= 11) {
                        mine[i][j + 1] = mine[i][j + 1] + 1;
                    }
                }
                if (i < n-1 && j > 0) {
                    if (mine[i + 1][j - 1] >= 11) {
                        mine[i + 1][j - 1] = mine[i + 1][j - 1] + 1;
                    }
                }
                if (i < n-1) {
                    if (mine[i + 1][j] >= 11) {
                        mine[i + 1][j] = mine[i + 1][j] + 1;
                    }
                }
                if (i < n-1 && j < m-1) {
                    if (mine[i + 1][j + 1] >= 11) {
                        mine[i + 1][j + 1] = mine[i + 1][j + 1] + 1;
                    }
                }
            }
        }
    }

    for(i = 0; i<n; i++) {
        for (j = 0; j < m; j++) {
            if(mine[i][j] >= 12 && mine[i][j] <= 19){
                mine[i][j] = mine[i][j] - 1;
            }
        }
    }

    open(x-1, y-1, n, m, mine, ch);
    printmine(mine, m, n);

}


//ektypwsh tablo
    void printmine(int** mine, int m, int n){
        int i,j;
        printf("   ");
        for (j = 0; j < m; j++) {
            if(j < 8) {
                printf(" %d ", j + 1);
            }
            else
                printf(" %d", j+1);
        }
        printf("\n");
        for (j = 0; j < n+1; j++) {
            printf("---");
        }
        printf("\n");
        for(i = 0; i<n; i++){
            if(i < 9) {
                printf(" %d|", i + 1);
            }
            else{
                printf("%d|", i + 1);
            }
            for(j = 0; j<m; j++){
                if(mine[i][j] == 9){
                    printf(" # ");
                }
                if(mine[i][j] == 10){
                    printf(" # ");
                }

                if(mine[i][j] == 1){
                    printf(" 1 ");
                }

                if(mine[i][j] == 2){
                    printf(" 2 ");
                }

                if(mine[i][j] == 3){
                    printf(" 3 ");
                }

                if(mine[i][j] == 4){
                    printf(" 4 ");
                }

                if(mine[i][j] == 5){
                    printf(" 5 ");
                }

                if(mine[i][j] == 6){
                    printf(" 6 ");
                }

                if(mine[i][j] == 7){
                    printf(" 7 ");
                }

                if(mine[i][j] == 8){
                    printf(" 8 ");
                }

                if(mine[i][j] == 20){
                    printf(" @ ");
                }

                if(mine[i][j] == 0){
                    printf(" . ");
                }

                if(mine[i][j] >= 11 && mine[i][j] <= 18 ){
                    printf(" # ");
               }
            }
            printf("\n");
        }
    }

void cheat(int x, int y, int** mine, char ch[50]){
    x--;
    y--;
    if(mine[x][y] == 9){
        printf("This square is empty\n");
    }
    else if(mine[x][y] == 10){
        printf("This square is a mine\n");
    }
    else if(mine[x][y] >= 11 && mine[x][y]<= 18){
        printf("This square is a neighboring square of a mine. It is close to %d mines\n", mine[x][y]-10);
    }
    else if(mine[x][y] == 20){
        printf("This square has been flagged\n");
    }
    else{
        printf("This square is already open\n");
    }
}

void mark(int count, int x, int y, int** mine, int n, int m, char ch[50], mark_coords** mc){
    x--;
    y--;
    if(mine[x][y] >= 9 && mine[x][y] <= 18) {
        mc[x][y].x = x;
        mc[x][y].y = y;
        mc[x][y].type = mine[x][y];
        mine[x][y] = 20;
        printf("Position (%d,%d)" " has been marked\n", x + 1, y + 1);
    }
    else{
        printf("Position (%d,%d)" " is already marked\n", x + 1, y + 1);
    }
}

void unmark(int count, int x, int y, int** mine, int n, int m, char ch[50], mark_coords** mc){
    x--;
    y--;
    int i, j;
    if(mine[x][y] == 20) {
        printf("Position (%d,%d)" " has been unmarked\n", x + 1, y + 1);
        printf("%d", mc[x][y].type);
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                mine[x][y] = mc[x][y].type;
            }
        }
    }
    else{
        printf("Position (%d,%d)" " has not been marked\n", x + 1, y + 1);
    }
}

void open(int x, int y, int n, int m, int** mine, char ch[50]){
    if(mine[x][y] >= 0 && mine[x][y] <= 8){
        return;
    }

    if(mine[x][y] == 10){
        return;
    }
    if(mine[x][y] >= 11 && mine[x][y] <= 18){
        mine[x][y] = mine[x][y] % 10;
        return;
    }
    if(x < 0 || x >= n || y < 0 || y >= m ){
        return;
    }

    if(mine[x][y] == 9){
        mine[x][y] = 0;
        if (x + 1 < n) {
            open(x+1,y,n,m,mine,ch);
        }
        if (x - 1 >= 0) {
            open(x-1,y,n,m,mine,ch);
        }
        if (y + 1 < m) {
            open(x,y+1,n,m,mine,ch);
        }
        if (y - 1 >= 0) {
            open(x,y-1,n,m,mine,ch);
        }

    }
    if(mine[x][y] >= 11 && mine[x][y] <= 18 ){
        mine[x][y] = mine[x][y] % 10;
    }
}