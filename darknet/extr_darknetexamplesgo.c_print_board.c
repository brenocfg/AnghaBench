#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ inverted ; 
 int nind ; 
 scalar_t__ noi ; 
 int occupied (float*,int) ; 

void print_board(FILE *stream, float *board, int player, int *indexes)
{
    int i,j,n;
    fprintf(stream, "   ");
    for(i = 0; i < 19; ++i){
        fprintf(stream, "%c ", 'A' + i + 1*(i > 7 && noi));
    }
    fprintf(stream, "\n");
    for(j = 0; j < 19; ++j){
        fprintf(stream, "%2d", (inverted) ? 19-j : j+1);
        for(i = 0; i < 19; ++i){
            int index = j*19 + i;
            if(indexes){
                int found = 0;
                for(n = 0; n < nind; ++n){
                    if(index == indexes[n]){
                        found = 1;
                        /*
                           if(n == 0) fprintf(stream, "\uff11");
                           else if(n == 1) fprintf(stream, "\uff12");
                           else if(n == 2) fprintf(stream, "\uff13");
                           else if(n == 3) fprintf(stream, "\uff14");
                           else if(n == 4) fprintf(stream, "\uff15");
                         */
                        fprintf(stream, " %d", n+1);
                    }
                }
                if(found) continue;
            }
            //if(board[index]*-swap > 0) fprintf(stream, "\u25C9 ");
            //else if(board[index]*-swap < 0) fprintf(stream, "\u25EF ");
            if      (occupied(board, index) == player) fprintf(stream, " X");
            else if (occupied(board, index) ==-player) fprintf(stream, " O");
            else fprintf(stream, " .");
        }
        fprintf(stream, "\n");
    }
}