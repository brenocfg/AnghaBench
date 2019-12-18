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
 scalar_t__ makes_safe_go (float*,int*,int,int,int) ; 

int suicide_go(float *b, int p, int r, int c)
{
    int *l = calculate_liberties(b);
    int safe = 0;
    safe = safe || makes_safe_go(b, l, p, r+1, c);
    safe = safe || makes_safe_go(b, l, p, r-1, c);
    safe = safe || makes_safe_go(b, l, p, r, c+1);
    safe = safe || makes_safe_go(b, l, p, r, c-1);
    free(l);
    return !safe;
}