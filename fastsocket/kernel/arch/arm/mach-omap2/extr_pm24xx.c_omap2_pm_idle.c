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
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  omap2_can_sleep () ; 
 int /*<<< orphan*/  omap2_enter_full_retention () ; 
 int /*<<< orphan*/  omap2_enter_mpu_retention () ; 
 scalar_t__ omap_irq_pending () ; 

__attribute__((used)) static void omap2_pm_idle(void)
{
	local_irq_disable();
	local_fiq_disable();

	if (!omap2_can_sleep()) {
		if (omap_irq_pending())
			goto out;
		omap2_enter_mpu_retention();
		goto out;
	}

	if (omap_irq_pending())
		goto out;

	omap2_enter_full_retention();

out:
	local_fiq_enable();
	local_irq_enable();
}