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
 int /*<<< orphan*/  HYPERVISOR_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_poweroff ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static void xen_pm_power_off(void)
{
	local_irq_disable();
	HYPERVISOR_shutdown(SHUTDOWN_poweroff);
}