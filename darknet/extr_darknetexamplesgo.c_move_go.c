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
 int* calculate_liberties (float*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  remove_connected (float*,int*,int,int,int) ; 

void move_go(float *b, int p, int r, int c)
{
    int *l = calculate_liberties(b);
    if(p > 0) b[r*19 + c] = 1;
    else b[19*19 + r*19 + c] = 1;
    remove_connected(b, l, -p, r+1, c);
    remove_connected(b, l, -p, r-1, c);
    remove_connected(b, l, -p, r, c+1);
    remove_connected(b, l, -p, r, c-1);
    free(l);
}