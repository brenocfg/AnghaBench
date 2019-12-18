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

__attribute__((used)) static int ess_calc_div (int clock, int revert, int *speedp, int *diffp)
{
	int divider;
	int speed, diff;
	int retval;

	speed   = *speedp;
	divider = (clock + speed / 2) / speed;
	retval  = revert - divider;
	if (retval > revert - 1) {
		retval  = revert - 1;
		divider = revert - retval;
	}
	/* This line is suggested. Must be wrong I think
	*speedp = (clock + divider / 2) / divider;
	So I chose the next one */

	*speedp	= clock / divider;
	diff	= speed - *speedp;
	if (diff < 0) diff =-diff;
	*diffp  = diff;

	return retval;
}