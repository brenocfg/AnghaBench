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
struct sx_period {int period_ns; int reg_value; } ;

/* Variables and functions */
 int round_4 (unsigned int) ; 

__attribute__((used)) static void
calc_sx_table(unsigned int mhz, struct sx_period sx_table[9])
{
	unsigned int d, i;
	if (mhz < 11)
		d = 2;	/* divisor for  8-10 MHz input-clock */
	else if (mhz < 16)
		d = 3;	/* divisor for 12-15 MHz input-clock */
	else
		d = 4;	/* divisor for 16-20 MHz input-clock */

	d = (100000 * d) / 2 / mhz; /* 100 x DTCC / nanosec */

	sx_table[0].period_ns = 1;
	sx_table[0].reg_value = 0x20;
	for (i = 1; i < 8; i++) {
		sx_table[i].period_ns = round_4((i+1)*d / 100);
		sx_table[i].reg_value = (i+1)*0x10;
	}
	sx_table[7].reg_value = 0;
	sx_table[8].period_ns = 0;
	sx_table[8].reg_value = 0;
}