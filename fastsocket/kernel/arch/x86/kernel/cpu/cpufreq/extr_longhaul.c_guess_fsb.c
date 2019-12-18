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
 int ROUNDING ; 
 int cpu_khz ; 

__attribute__((used)) static int guess_fsb(int mult)
{
	int speed = cpu_khz / 1000;
	int i;
	int speeds[] = { 666, 1000, 1333, 2000 };
	int f_max, f_min;

	for (i = 0; i < 4; i++) {
		f_max = ((speeds[i] * mult) + 50) / 100;
		f_max += (ROUNDING / 2);
		f_min = f_max - ROUNDING;
		if ((speed <= f_max) && (speed >= f_min))
			return speeds[i] / 10;
	}
	return 0;
}