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
 scalar_t__ SOFTIRQ_DISABLE_OFFSET ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dec_preempt_count () ; 
 int /*<<< orphan*/  do_softirq () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ in_irq () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ local_softirq_pending () ; 
 int /*<<< orphan*/  preempt_check_resched () ; 
 scalar_t__ softirq_count () ; 
 int /*<<< orphan*/  sub_preempt_count (scalar_t__) ; 
 int /*<<< orphan*/  trace_softirqs_on (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void _local_bh_enable_ip(unsigned long ip)
{
	WARN_ON_ONCE(in_irq() || irqs_disabled());
#ifdef CONFIG_TRACE_IRQFLAGS
	local_irq_disable();
#endif
	/*
	 * Are softirqs going to be turned on now:
	 */
	if (softirq_count() == SOFTIRQ_DISABLE_OFFSET)
		trace_softirqs_on(ip);
	/*
	 * Keep preemption disabled until we are done with
	 * softirq processing:
 	 */
	sub_preempt_count(SOFTIRQ_DISABLE_OFFSET - 1);

	if (unlikely(!in_interrupt() && local_softirq_pending()))
		do_softirq();

	dec_preempt_count();
#ifdef CONFIG_TRACE_IRQFLAGS
	local_irq_enable();
#endif
	preempt_check_resched();
}