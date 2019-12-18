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
 int /*<<< orphan*/  __set_LEDS (int) ; 
 int /*<<< orphan*/  frv_cpu_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  pdm_suspend_mode ; 

int pm_do_suspend(void)
{
	local_irq_disable();

	__set_LEDS(0xb1);

	/* go zzz */
	frv_cpu_suspend(pdm_suspend_mode);

	__set_LEDS(0xb2);

	local_irq_enable();

	return 0;
}