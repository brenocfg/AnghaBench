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
 int ess_calc_div (int,int,int*,int*) ; 

__attribute__((used)) static int ess_calc_best_speed
	(int clock1, int rev1, int clock2, int rev2, int *divp, int *speedp)
{
	int speed1 = *speedp, speed2 = *speedp;
	int div1, div2;
	int diff1, diff2;
	int retval;

	div1 = ess_calc_div (clock1, rev1, &speed1, &diff1);
	div2 = ess_calc_div (clock2, rev2, &speed2, &diff2);

	if (diff1 < diff2) {
		*divp   = div1;
		*speedp = speed1;
		retval  = 1;
	} else {
	/*	*divp   = div2; */
		*divp   = 0x80 | div2;
		*speedp = speed2;
		retval  = 2;
	}

	return retval;
}