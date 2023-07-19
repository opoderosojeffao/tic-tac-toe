#include <stdio.h>
#include <stdlib.h>

void printGame(char tic[3][3]);
char changeArray(char tic[3][3],  int pos, char playerChar);
char playerLetter(int player);
void play(int player, char tic[3][3], int * remainingPos);
int * removeArray(int *arr, int number, int size);
int isPositionPlayable(int *arr, int position);
int checkWinner(char tic[3][3]);
int isEqual(char * arr);
int getPlayer(char playerLetter);

#define G_POS 10

int main() 
{
    // grid and positions
    char tic[3][3]  = {'1', '2', '3', 
                    '4', '5', '6',
                    '7', '8', '9'};

    int remainingPos[G_POS] = {1,2,3,4,5,6,7,8,9,-1}; // Position available to be played

    // Maximum number of turns
    int gameTime = G_POS;
    int playerTurn = 1; // Player 1 starts playing

    printGame(tic);

    while (gameTime != 1)
    {
        play(playerTurn, tic, remainingPos);
        if(playerTurn == 1) 
        {
            playerTurn = 2;
        } else 
        {
            playerTurn = 1;
        }

        if(checkWinner(tic) == 1 || checkWinner(tic) == 2)
        {   
            printf("The game has ended, player %d won\n", checkWinner(tic));
            break;
        }
        gameTime--;
    }

    if(gameTime <= 1)
    {
        printf("\nThe game has finished, no one won :(");
    }

    return 0;
}

// Function that prints the board
void printGame(char tic[3][3]) 
{
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", tic[i][j]);
            if (j != 2)
                printf("| ");
        }
        printf("\n");
    }
}

// Change the element of the arry for the letter of the player
char changeArray(char tic[3][3],  int pos, char playerChar)
{
    // from top left to right
    // 1 2 3
    // 4 5 6
    // 7 8 9

    switch(pos)
    {
        case 1:
            tic[0][0] = playerChar;
            break;
        case 2:
            tic[0][1] = playerChar;
            break;
        case 3:
            tic[0][2] = playerChar;
            break;
        case 4:
            tic[1][0] = playerChar;
            break;
        case 5:
            tic[1][1] = playerChar;
            break;
        case 6:
            tic[1][2] = playerChar;
            break;
        case 7:
            tic[2][0] = playerChar;
            break;
        case 8:
            tic[2][1] = playerChar;
            break;
        case 9:
            tic[2][2] = playerChar;
            break;
    }

    return tic[3][3];
}

// Return player letter
char playerLetter(int player)
{
    if (player == 1) 
        return 'X';
    return 'O';
}

// Function including all the action necessary for the player to play
// scanning input and updating the game
void play(int player, char tic[3][3], int * remainingPos)
{
    int position;
    printf("Player %d (%c) turn: ", player, playerLetter(player));
    
    while(1)
    {
        scanf("%d", &position);

        if (isPositionPlayable(remainingPos, position) == 1) 
        {
            changeArray(tic, position, playerLetter(player));
            printGame(tic);
            removeArray(remainingPos, position, G_POS);
            break;
        } 
        printf("\nPostion %d cannot be played, please play another one: ", position);
    }

}

// Remove the available position in the position array
// used to make sure that the player cannot play in a place that was already used.
int * removeArray(int *arr, int number, int size) 
{   
    arr[number-1] = -1;
    
    return arr;
}

// Check if the position is available (array)
int isPositionPlayable(int *arr, int position)
{
    for (int i = 0; i < G_POS; i++)
    {
        if (position == arr[i])
            return 1;
    }

    return 0;
}

// check if a row, column or diagonal was completed
int checkWinner(char tic[3][3])
{
    char col1[3]    = {tic[0][0], tic[1][0], tic[2][0]}; // 0,0
    char col2[3]    = {tic[0][1], tic[1][1], tic[2][1]}; // 1,1
    char col3[3]    = {tic[0][2], tic[1][2], tic[2][2]}; // 2,2
    char row1[3]    = {tic[0][0], tic[0][1], tic[0][2]}; // 0,0
    char row2[3]    = {tic[1][0], tic[1][1], tic[1][2]}; // 1,1
    char row3[3]    = {tic[2][0], tic[2][1], tic[2][2]}; // 2,2
    char diag[3]    = {tic[0][0], tic[1][1], tic[2][2]}; // 1,1
    char invDiag[3] = {tic[0][2], tic[1][1], tic[2][0]}; // 1,1 

    if(isEqual(col1) || isEqual(row1))
    {
        //printf("col1 or row1");
        return getPlayer(tic[0][0]);
    } 
    else if (isEqual(col2) || isEqual(row2) || isEqual(diag) || isEqual(invDiag))
    {
        //printf("col2, row2, or diag");
        return getPlayer(tic[1][1]);
    } 
    else if (isEqual(col3) || isEqual(row3))
    {
        //printf("col3 or row3");
        return getPlayer(tic[2][2]);
    }

    return -1; // draw
}

// Check if all elements on the line are the same (end game)
int isEqual(char * arr)
{
    if(arr[0] == arr[1] && arr[0] == arr[2])
        return 1;

    return 0;
}

// return player number based on the letter (X or O)
int getPlayer(char playerLetter)
{
    if(playerLetter == 'X')
    {
        return 1;
    }

    return 2;
}