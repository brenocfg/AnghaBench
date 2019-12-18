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
 int /*<<< orphan*/  TIF_MCCK_PENDING ; 
 int /*<<< orphan*/  cpu_die () ; 
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_mcck_disable () ; 
 int /*<<< orphan*/  local_mcck_enable () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  s390_handle_mcck () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 
 int /*<<< orphan*/  vtime_stop_cpu () ; 

__attribute__((used)) static void default_idle(void)
{
	/* CPU is going idle. */
	local_irq_disable();
	if (need_resched()) {
		local_irq_enable();
		return;
	}
#ifdef CONFIG_HOTPLUG_CPU
	if (cpu_is_offline(smp_processor_id())) {
		preempt_enable_no_resched();
		cpu_die();
	}
#endif
	local_mcck_disable();
	if (test_thread_flag(TIF_MCCK_PENDING)) {
		local_mcck_enable();
		local_irq_enable();
		s390_handle_mcck();
		return;
	}
	trace_hardirqs_on();
	/* Don't trace preempt off for idle. */
	stop_critical_timings();
	/* Stop virtual timer and halt the cpu. */
	vtime_stop_cpu();
	/* Reenable preemption tracer. */
	start_critical_timings();
}