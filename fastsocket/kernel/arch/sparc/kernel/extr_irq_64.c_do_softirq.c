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
 int STACK_BIAS ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  __do_softirq () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ local_softirq_pending () ; 
 size_t smp_processor_id () ; 
 void** softirq_stack ; 

void do_softirq(void)
{
	unsigned long flags;

	if (in_interrupt())
		return;

	local_irq_save(flags);

	if (local_softirq_pending()) {
		void *orig_sp, *sp = softirq_stack[smp_processor_id()];

		sp += THREAD_SIZE - 192 - STACK_BIAS;

		__asm__ __volatile__("mov %%sp, %0\n\t"
				     "mov %1, %%sp"
				     : "=&r" (orig_sp)
				     : "r" (sp));
		__do_softirq();
		__asm__ __volatile__("mov %0, %%sp"
				     : : "r" (orig_sp));
	}

	local_irq_restore(flags);
}