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
 int /*<<< orphan*/  HSR0_PDM_BUS_SLEEP ; 
 int /*<<< orphan*/  __power_switch_wake_check () ; 
 int /*<<< orphan*/  __power_switch_wake_cleanup () ; 
 int /*<<< orphan*/  __power_switch_wake_setup () ; 
 int /*<<< orphan*/  __set_LEDS (int) ; 
 int /*<<< orphan*/  frv_cpu_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

int pm_do_bus_sleep(void)
{
	local_irq_disable();

	/*
         * Here is where we need some platform-dependent setup
	 * of the interrupt state so that appropriate wakeup
	 * sources are allowed and all others are masked.
	 */
	__power_switch_wake_setup();

	__set_LEDS(0xa1);

	/* go zzz
	 *
	 * This is in a loop in case power switch shares an irq with other
	 * devices. The wake_check() tells us if we need to finish waking
	 * or go back to sleep.
	 */
	do {
		frv_cpu_suspend(HSR0_PDM_BUS_SLEEP);
	} while (__power_switch_wake_check && !__power_switch_wake_check());

	__set_LEDS(0xa2);

	/*
         * Here is where we need some platform-dependent restore
	 * of the interrupt state prior to being called.
	 */
	__power_switch_wake_cleanup();

	local_irq_enable();

	return 0;
}