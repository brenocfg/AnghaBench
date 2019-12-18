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
 int /*<<< orphan*/  idle_with_irq_disabled () ; 
 int /*<<< orphan*/  ipipe_suspend_domain () ; 
 int /*<<< orphan*/  local_irq_disable_hw () ; 
 int /*<<< orphan*/  local_irq_enable_hw () ; 
 int /*<<< orphan*/  need_resched () ; 

__attribute__((used)) static void default_idle(void)
{
#ifdef CONFIG_IPIPE
	ipipe_suspend_domain();
#endif
	local_irq_disable_hw();
	if (!need_resched())
		idle_with_irq_disabled();

	local_irq_enable_hw();
}