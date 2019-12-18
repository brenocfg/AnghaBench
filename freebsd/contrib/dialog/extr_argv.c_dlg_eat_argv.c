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
 int TRUE ; 

int
dlg_eat_argv(int *argcp, char ***argvp, int start, int count)
{
    int k;

    *argcp -= count;
    for (k = start; k <= *argcp; k++)
	(*argvp)[k] = (*argvp)[k + count];
    (*argvp)[*argcp] = 0;
    return TRUE;
}