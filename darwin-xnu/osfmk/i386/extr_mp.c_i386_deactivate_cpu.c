#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_7__ {scalar_t__ cpu_signals; TYPE_1__ rtclock_timer; int /*<<< orphan*/  cpu_running; } ;
typedef  TYPE_2__ cpu_data_t ;
struct TYPE_8__ {scalar_t__ rtcDeadline; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ EndOfAllTime ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRACE_MP_CPU_DEACTIVATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/  cpu_to_cpumask (int /*<<< orphan*/ ) ; 
 TYPE_2__* current_cpu_datap () ; 
 int /*<<< orphan*/  master_cpu ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt_cpu_down (TYPE_2__*) ; 
 int /*<<< orphan*/  setPop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_queue_expire_local ; 
 int /*<<< orphan*/  timer_queue_shutdown (int /*<<< orphan*/ *) ; 
 TYPE_3__* x86_lcpu () ; 
 int /*<<< orphan*/  x86_topo_lock ; 

void
i386_deactivate_cpu(void)
{
	cpu_data_t	*cdp = current_cpu_datap();

	assert(!ml_get_interrupts_enabled());
 
	KERNEL_DEBUG_CONSTANT(
		TRACE_MP_CPU_DEACTIVATE | DBG_FUNC_START,
		0, 0, 0, 0, 0);

	mp_safe_spin_lock(&x86_topo_lock);
	cdp->cpu_running = FALSE;
	simple_unlock(&x86_topo_lock);

	/*
	 * Move all of this cpu's timers to the master/boot cpu,
	 * and poke it in case there's a sooner deadline for it to schedule.
	 */
	timer_queue_shutdown(&cdp->rtclock_timer.queue);
	mp_cpus_call(cpu_to_cpumask(master_cpu), ASYNC, timer_queue_expire_local, NULL);

#if MONOTONIC
	mt_cpu_down(cdp);
#endif /* MONOTONIC */

	/*
	 * Open an interrupt window
	 * and ensure any pending IPI or timer is serviced
	 */
	mp_disable_preemption();
	ml_set_interrupts_enabled(TRUE);

	while (cdp->cpu_signals && x86_lcpu()->rtcDeadline != EndOfAllTime)
		cpu_pause();
	/*
	 * Ensure there's no remaining timer deadline set
	 * - AICPM may have left one active.
	 */
	setPop(0);

	ml_set_interrupts_enabled(FALSE);
	mp_enable_preemption();

	KERNEL_DEBUG_CONSTANT(
		TRACE_MP_CPU_DEACTIVATE | DBG_FUNC_END,
		0, 0, 0, 0, 0);
}