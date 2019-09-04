#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ mp_call_queue_t ;
typedef  int cpumask_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CROSSCALL_TIMEOUT ; 
 int /*<<< orphan*/  NMIPI_panic (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t cpu_number () ; 
 int /*<<< orphan*/  cpu_signal_handler (int /*<<< orphan*/ *) ; 
 scalar_t__ get_preemption_level () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mp_cpus_call_action () ; 
 TYPE_1__* mp_cpus_call_head ; 
 scalar_t__ mp_spin_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtsc64 () ; 

__attribute__((used)) static void
mp_cpus_call_wait(boolean_t	intrs_enabled,
		  cpumask_t	cpus_called,
		  cpumask_t	*cpus_responded)
{
	mp_call_queue_t		*cqp;
	uint64_t		tsc_spin_start;

	assert(ml_get_interrupts_enabled() == 0 || get_preemption_level() != 0);
	cqp = &mp_cpus_call_head[cpu_number()];

	tsc_spin_start = rdtsc64();
	while (*cpus_responded != cpus_called) {
		if (!intrs_enabled) {
			/* Sniffing w/o locking */
			if (!queue_empty(&cqp->queue))
				mp_cpus_call_action();
			cpu_signal_handler(NULL);
		}
		if (mp_spin_timeout(tsc_spin_start)) {
			cpumask_t	cpus_unresponsive;

			cpus_unresponsive = cpus_called & ~(*cpus_responded);
			NMIPI_panic(cpus_unresponsive, CROSSCALL_TIMEOUT);
			panic("mp_cpus_call_wait() timeout, cpus: 0x%llx",
				cpus_unresponsive);
		}
	}
}