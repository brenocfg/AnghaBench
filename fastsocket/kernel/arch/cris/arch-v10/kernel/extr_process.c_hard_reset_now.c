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
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  start ; 

void hard_reset_now (void)
{
	/*
	 * Don't declare this variable elsewhere.  We don't want any other
	 * code to know about it than the watchdog handler in entry.S and
	 * this code, implementing hard reset through the watchdog.
	 */
#if defined(CONFIG_ETRAX_WATCHDOG) && !defined(CONFIG_SVINTO_SIM)
	extern int cause_of_death;
#endif

	printk("*** HARD RESET ***\n");
	local_irq_disable();

#if defined(CONFIG_ETRAX_WATCHDOG) && !defined(CONFIG_SVINTO_SIM)
	cause_of_death = 0xbedead;
#else
	/* Since we dont plan to keep on resetting the watchdog,
	   the key can be arbitrary hence three */
	*R_WATCHDOG = IO_FIELD(R_WATCHDOG, key, 3) |
		IO_STATE(R_WATCHDOG, enable, start);
#endif

	while(1) /* waiting for RETRIBUTION! */ ;
}