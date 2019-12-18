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
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rdtsc_barrier () ; 
 int /*<<< orphan*/  rdtscl (unsigned long) ; 
 int /*<<< orphan*/  rep_nop () ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void delay_tsc(unsigned long loops)
{
	unsigned long bclock, now;
	int cpu;

	preempt_disable();
	cpu = smp_processor_id();
	rdtsc_barrier();
	rdtscl(bclock);
	for (;;) {
		rdtsc_barrier();
		rdtscl(now);
		if ((now - bclock) >= loops)
			break;

		/* Allow RT tasks to run */
		preempt_enable();
		rep_nop();
		preempt_disable();

		/*
		 * It is possible that we moved to another CPU, and
		 * since TSC's are per-cpu we need to calculate
		 * that. The delay must guarantee that we wait "at
		 * least" the amount of time. Being moved to another
		 * CPU could make the wait longer but we just need to
		 * make sure we waited long enough. Rebalance the
		 * counter for this CPU.
		 */
		if (unlikely(cpu != smp_processor_id())) {
			loops -= (now - bclock);
			cpu = smp_processor_id();
			rdtsc_barrier();
			rdtscl(bclock);
		}
	}
	preempt_enable();
}