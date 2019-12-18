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
typedef  int u32 ;
typedef  int suspend_state_t ;

/* Variables and functions */
 int EINVAL ; 
 int PM_SUSPEND_MAX ; 
 int PM_SUSPEND_MEM ; 
 int PM_SUSPEND_STANDBY ; 
 int hibernate () ; 
 int pm_suspend (int) ; 

int acpi_suspend(u32 acpi_state)
{
	suspend_state_t states[] = {
		[1] = PM_SUSPEND_STANDBY,
		[3] = PM_SUSPEND_MEM,
		[5] = PM_SUSPEND_MAX
	};

	if (acpi_state < 6 && states[acpi_state])
		return pm_suspend(states[acpi_state]);
	if (acpi_state == 4)
		return hibernate();
	return -EINVAL;
}