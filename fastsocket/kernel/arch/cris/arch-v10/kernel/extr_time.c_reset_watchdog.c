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
 int IO_FIELD (int*,int /*<<< orphan*/ ,int) ; 
 int IO_STATE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* R_WATCHDOG ; 
 scalar_t__ WATCHDOG_MIN_FREE_PAGES ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  key ; 
 scalar_t__ nr_free_pages () ; 
 int /*<<< orphan*/  start ; 
 int watchdog_key ; 

void
reset_watchdog(void)
{
#if defined(CONFIG_ETRAX_WATCHDOG) && !defined(CONFIG_SVINTO_SIM)
	/* only keep watchdog happy as long as we have memory left! */
	if(nr_free_pages() > WATCHDOG_MIN_FREE_PAGES) {
		/* reset the watchdog with the inverse of the old key */
		watchdog_key ^= 0x7; /* invert key, which is 3 bits */
		*R_WATCHDOG = IO_FIELD(R_WATCHDOG, key, watchdog_key) |
			IO_STATE(R_WATCHDOG, enable, start);
	}
#endif
}