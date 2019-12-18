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
 int /*<<< orphan*/  __irq_enter () ; 
 int /*<<< orphan*/  _local_bh_enable () ; 
 scalar_t__ idle_cpu (int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  rcu_irq_enter () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tick_check_idle (int) ; 

void irq_enter(void)
{
	int cpu = smp_processor_id();

	rcu_irq_enter();
	if (idle_cpu(cpu) && !in_interrupt()) {
		/*
		 * Prevent raise_softirq from needlessly waking up ksoftirqd
		 * here, as softirq will be serviced on return from interrupt.
		 */
		local_bh_disable();
		tick_check_idle(cpu);
		_local_bh_enable();
	}

	__irq_enter();
}