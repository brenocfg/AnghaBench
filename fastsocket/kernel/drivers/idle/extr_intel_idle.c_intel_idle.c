#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_state {int dummy; } ;
struct cpuidle_device {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_BROADCAST_ENTER ; 
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_BROADCAST_EXIT ; 
 unsigned long MWAIT_CSTATE_MASK ; 
 unsigned long MWAIT_SUBSTATE_SIZE ; 
 int /*<<< orphan*/  POWER_CSTATE ; 
 int /*<<< orphan*/  __monitor (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mwait (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clockevents_notify (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ cpuidle_get_statedata (struct cpuidle_state*) ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int lapic_timer_reliable_states ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 int /*<<< orphan*/  trace_power_start (int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static int intel_idle(struct cpuidle_device *dev, struct cpuidle_state *state)
{
	unsigned long ecx = 1; /* break on interrupt flag */
	unsigned long eax = (unsigned long)cpuidle_get_statedata(state);
	unsigned int cstate;
	ktime_t kt_before, kt_after;
	s64 usec_delta;
	int cpu = smp_processor_id();

	cstate = (((eax) >> MWAIT_SUBSTATE_SIZE) & MWAIT_CSTATE_MASK) + 1;

	local_irq_disable();

	if (!(lapic_timer_reliable_states & (1 << (cstate))))
		clockevents_notify(CLOCK_EVT_NOTIFY_BROADCAST_ENTER, &cpu);

	kt_before = ktime_get_real();

	stop_critical_timings();
#ifndef MODULE
	trace_power_start(POWER_CSTATE, (eax >> 4) + 1, cpu);
#endif
	if (!need_resched()) {

		__monitor((void *)&current_thread_info()->flags, 0, 0);
		smp_mb();
		if (!need_resched())
			__mwait(eax, ecx);
	}

	start_critical_timings();

	kt_after = ktime_get_real();
	usec_delta = ktime_to_us(ktime_sub(kt_after, kt_before));

	local_irq_enable();

	if (!(lapic_timer_reliable_states & (1 << (cstate))))
		clockevents_notify(CLOCK_EVT_NOTIFY_BROADCAST_EXIT, &cpu);

	return usec_delta;
}