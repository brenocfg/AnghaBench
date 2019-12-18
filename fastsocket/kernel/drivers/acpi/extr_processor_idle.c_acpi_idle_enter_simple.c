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
struct acpi_processor_cx {scalar_t__ entry_method; scalar_t__ type; int time; int /*<<< orphan*/  usage; } ;
struct acpi_processor {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ ACPI_CSTATE_FFH ; 
 int /*<<< orphan*/  ACPI_FLUSH_CPU_CACHE () ; 
 scalar_t__ ACPI_STATE_C3 ; 
 int PM_TIMER_TICK_NS ; 
 int /*<<< orphan*/  TS_POLLING ; 
 struct acpi_processor* __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_idle_do_entry (struct acpi_processor_cx*) ; 
 int acpi_idle_enter_c1 (struct cpuidle_device*,struct cpuidle_state*) ; 
 scalar_t__ acpi_idle_suspend ; 
 struct acpi_processor_cx* cpuidle_get_statedata (struct cpuidle_state*) ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_timer_state_broadcast (struct acpi_processor*,struct acpi_processor_cx*,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int need_resched () ; 
 int /*<<< orphan*/  processors ; 
 int /*<<< orphan*/  sched_clock_idle_sleep_event () ; 
 int /*<<< orphan*/  sched_clock_idle_wakeup_event (int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 
 int us_to_pm_timer_ticks (int) ; 

__attribute__((used)) static int acpi_idle_enter_simple(struct cpuidle_device *dev,
				  struct cpuidle_state *state)
{
	struct acpi_processor *pr;
	struct acpi_processor_cx *cx = cpuidle_get_statedata(state);
	ktime_t  kt1, kt2;
	s64 idle_time;
	s64 sleep_ticks = 0;

	pr = __get_cpu_var(processors);

	if (unlikely(!pr))
		return 0;

	if (acpi_idle_suspend)
		return(acpi_idle_enter_c1(dev, state));

	local_irq_disable();
	if (cx->entry_method != ACPI_CSTATE_FFH) {
		current_thread_info()->status &= ~TS_POLLING;
		/*
		 * TS_POLLING-cleared state must be visible before we test
		 * NEED_RESCHED:
		 */
		smp_mb();
	}

	if (unlikely(need_resched())) {
		current_thread_info()->status |= TS_POLLING;
		local_irq_enable();
		return 0;
	}

	/*
	 * Must be done before busmaster disable as we might need to
	 * access HPET !
	 */
	lapic_timer_state_broadcast(pr, cx, 1);

	if (cx->type == ACPI_STATE_C3)
		ACPI_FLUSH_CPU_CACHE();

	kt1 = ktime_get_real();
	/* Tell the scheduler that we are going deep-idle: */
	sched_clock_idle_sleep_event();
	acpi_idle_do_entry(cx);
	kt2 = ktime_get_real();
	idle_time =  ktime_to_us(ktime_sub(kt2, kt1));

	sleep_ticks = us_to_pm_timer_ticks(idle_time);

	/* Tell the scheduler how much we idled: */
	sched_clock_idle_wakeup_event(sleep_ticks*PM_TIMER_TICK_NS);

	local_irq_enable();
	current_thread_info()->status |= TS_POLLING;

	cx->usage++;

	lapic_timer_state_broadcast(pr, cx, 0);
	cx->time += sleep_ticks;
	return idle_time;
}