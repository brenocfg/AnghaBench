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
struct sx_period {int period_ns; } ;

/* Variables and functions */

__attribute__((used)) static int
round_period(unsigned int period, const struct sx_period *sx_table)
{
	int x;

	for (x = 1; sx_table[x].period_ns; x++) {
		if ((period <= sx_table[x - 0].period_ns) &&
		    (period > sx_table[x - 1].period_ns)) {
			return x;
		}
	}
	return 7;
}