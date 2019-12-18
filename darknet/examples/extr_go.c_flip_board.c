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

void flip_board(float *board)
{
    int i;
    for(i = 0; i < 19*19; ++i){
        float swap = board[i];
        board[i] = board[i+19*19];
        board[i+19*19] = swap;
        board[i+19*19*2] = 1-board[i+19*19*2];
    }
}