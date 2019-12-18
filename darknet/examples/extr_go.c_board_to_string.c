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

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void board_to_string(char *s, float *board)
{
    int i, j;
    memset(s, 0, (19*19/4+1)*sizeof(char));
    int count = 0;
    for(i = 0; i < 91; ++i){
        for(j = 0; j < 4; ++j){
            int me = (board[count] == 1);
            int you = (board[count + 19*19] == 1);
            if (me) s[i] = s[i] | (1<<(2*j));
            if (you) s[i] = s[i] | (1<<(2*j + 1));
            ++count;
            if(count >= 19*19) break;
        }
    }
}