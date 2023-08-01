#include <stdio.h>
#include <stdbool.h>



/*
 * Function:  positionInBounds
 * ------------------------------
 * Check if the position is in the bound of the board 
 *
 * returns: If the position is in the bound of the board, return true
 *          If the position is out of the bound of the board, return false 
 */
bool positionInBounds(int n, int row, int col) {
    bool inBound = true;

    if(row < 0 || row >= n || col < 0 || col >= n){
        inBound = false;
    }
    return inBound;
}

/*
 * Function:  checkLegalInDirection
 * ------------------------------
 * Check if the direction is aviable to place tile 
 *
 * returns: If the position is aviable to place tile, return true
 *          If the position is not aviable to place tile , return false 
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
    int newRow, newCol;
    char opponent = (colour == 'B') ? 'W' : 'B';

    //when the position is on the board 
    if(row + deltaRow < n && row + deltaRow >= 0 && col + deltaCol < n 
        && col + deltaCol >= 0 && (deltaRow != 0 || deltaCol != 0)){
        //if there is a oppoent at the position
        if(board[row+deltaRow][col+deltaCol] == opponent){ 
            newRow = deltaRow + row;
            newCol = deltaCol + col;
                            
            while(1){
                newRow += deltaRow;
                newCol += deltaCol;
                
                //the position is out of the board
                if(newRow >= n || newRow < 0 || newCol >= n || newCol < 0){  
                   break;
                }else if(board[newRow][newCol] == 'U'){ //the position is empty
                    break;
                }else if(board[newRow][newCol] == colour){//the position has a same colour tile
                    return true;
                }          
            }

        }
    }
    return false;
}

int main(void) {
    int n = 4, deltaRow, deltaCol, newRow, newCol;
    char colour = 'B', rowC = 'a', colC = 'f';     
    bool valid = false;
    char avaPosR[100000] = {0}; 
    char avaPosC[100000] = {0}; 
    char board[26][26];

    if(positionInBounds(n, rowC - 'a', colC - 'a')){
    if(board[rowC -'a'][colC -'a'] == 'U'){//check if the position is empty
        for(deltaRow = -1; deltaRow <= 1; deltaRow++){
            for(deltaCol = -1; deltaCol <= 1; deltaCol++){
                if(checkLegalInDirection(board, n, rowC - 'a', colC - 'a', 
                    colour, deltaRow, deltaCol)){
                    
                    board[rowC-'a'][colC-'a'] = colour; //change the colour of the position

                    newRow = deltaRow + (rowC -'a');
                    newCol = deltaCol + (colC -'a');

                    //change the colour of the tiles between the two same colour tiles    
                    while(board[newRow][newCol] != colour && board[newRow][newCol] != 'U'){
                        board[newRow][newCol] = colour;
                        newRow += deltaRow;
                        newCol += deltaCol;
                    }
                    if(colour == 'W' || 'B'){
                        valid = true;
                    }
                }
            }
        }
    }
    }

    if(valid){
        printf("Valid move for %c at %c%c\n", colour, rowC, colC);
    }else{
        printf("Invalid move for %c at %c%c\n", colour, rowC, colC);
    }

  return 0;
}
