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
typedef  scalar_t__ suspend_state_t ;

/* Variables and functions */
 scalar_t__ PM_SUSPEND_MEM ; 
 scalar_t__ PM_SUSPEND_STANDBY ; 

__attribute__((used)) static int bfin_pm_valid(suspend_state_t state)
{
	return (state == PM_SUSPEND_STANDBY
#if !(defined(BF533_FAMILY) || defined(CONFIG_BF561))
	/*
	 * On BF533/2/1:
	 * If we enter Hibernate the SCKE Pin is driven Low,
	 * so that the SDRAM enters Self Refresh Mode.
	 * However when the reset sequence that follows hibernate
	 * state is executed, SCKE is driven High, taking the
	 * SDRAM out of Self Refresh.
	 *
	 * If you reconfigure and access the SDRAM "very quickly",
	 * you are likely to avoid errors, otherwise the SDRAM
	 * start losing its contents.
	 * An external HW workaround is possible using logic gates.
	 */
	|| state == PM_SUSPEND_MEM
#endif
	);
}