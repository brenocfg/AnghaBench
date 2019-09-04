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
 int occupied (float*,int) ; 

int print_game(float *board, FILE *fp)
{
    int i, j;
    int count = 3;
    fprintf(fp, "komi 6.5\n");
    fprintf(fp, "boardsize 19\n");
    fprintf(fp, "clear_board\n");
    for(j = 0; j < 19; ++j){
        for(i = 0; i < 19; ++i){
            if(occupied(board,j*19 + i) == 1) fprintf(fp, "play black %c%d\n", 'A'+i+(i>=8), 19-j);
            if(occupied(board,j*19 + i) == -1) fprintf(fp, "play white %c%d\n", 'A'+i+(i>=8), 19-j);
            if(occupied(board,j*19 + i)) ++count;
        }
    }
    return count;
}