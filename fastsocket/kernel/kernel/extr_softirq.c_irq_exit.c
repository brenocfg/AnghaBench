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
 int /*<<< orphan*/  IRQ_EXIT_OFFSET ; 
 int /*<<< orphan*/  account_system_vtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ idle_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  invoke_softirq () ; 
 scalar_t__ local_softirq_pending () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  rcu_irq_exit () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  sub_preempt_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hardirq_exit () ; 

void irq_exit(void)
{
	account_system_vtime(current);
	trace_hardirq_exit();
	sub_preempt_count(IRQ_EXIT_OFFSET);
	if (!in_interrupt() && local_softirq_pending())
		invoke_softirq();

#ifdef CONFIG_NO_HZ
	/* Make sure that timer wheel updates are propagated */
	rcu_irq_exit();
	if (idle_cpu(smp_processor_id()) && !in_interrupt() && !need_resched())
		tick_nohz_stop_sched_tick(0);
#endif
	preempt_enable_no_resched();
}