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
 scalar_t__ c0_compare_int_pending () ; 
 int /*<<< orphan*/  compare_change_hazard () ; 
 unsigned int read_c0_count () ; 
 int /*<<< orphan*/  write_c0_compare (unsigned int) ; 

int c0_compare_int_usable(void)
{
	unsigned int delta;
	unsigned int cnt;

	/*
	 * IP7 already pending?  Try to clear it by acking the timer.
	 */
	if (c0_compare_int_pending()) {
		write_c0_compare(read_c0_count());
		compare_change_hazard();
		if (c0_compare_int_pending())
			return 0;
	}

	for (delta = 0x10; delta <= 0x400000; delta <<= 1) {
		cnt = read_c0_count();
		cnt += delta;
		write_c0_compare(cnt);
		compare_change_hazard();
		if ((int)(read_c0_count() - cnt) < 0)
		    break;
		/* increase delta if the timer was already expired */
	}

	while ((int)(read_c0_count() - cnt) <= 0)
		;	/* Wait for expiry  */

	compare_change_hazard();
	if (!c0_compare_int_pending())
		return 0;

	write_c0_compare(read_c0_count());
	compare_change_hazard();
	if (c0_compare_int_pending())
		return 0;

	/*
	 * Feels like a real count / compare timer.
	 */
	return 1;
}