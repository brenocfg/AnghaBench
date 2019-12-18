#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_state {int dummy; } ;
struct cpuidle_device {TYPE_2__* safe_state; TYPE_2__* last_state; } ;
struct acpi_processor_cx {scalar_t__ entry_method; int time; int /*<<< orphan*/  usage; int /*<<< orphan*/  bm_sts_skip; } ;
struct TYPE_4__ {scalar_t__ bm_control; scalar_t__ bm_check; } ;
struct acpi_processor {TYPE_1__ flags; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int (* enter ) (struct cpuidle_device*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_ARB_DISABLE ; 
 scalar_t__ ACPI_CSTATE_FFH ; 
 int /*<<< orphan*/  ACPI_FLUSH_CPU_CACHE () ; 
 int PM_TIMER_TICK_NS ; 
 int /*<<< orphan*/  TS_POLLING ; 
 struct acpi_processor* __get_cpu_var (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_idle_bm_check () ; 
 int /*<<< orphan*/  acpi_idle_do_entry (struct acpi_processor_cx*) ; 
 int acpi_idle_enter_c1 (struct cpuidle_device*,struct cpuidle_state*) ; 
 scalar_t__ acpi_idle_suspend ; 
 int /*<<< orphan*/  acpi_safe_halt () ; 
 int /*<<< orphan*/  acpi_unlazy_tlb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,int) ; 
 scalar_t__ c3_cpu_count ; 
 int /*<<< orphan*/  c3_lock ; 
 struct acpi_processor_cx* cpuidle_get_statedata (struct cpuidle_state*) ; 
 TYPE_3__* current_thread_info () ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_timer_state_broadcast (struct acpi_processor*,struct acpi_processor_cx*,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int need_resched () ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  processors ; 
 int /*<<< orphan*/  sched_clock_idle_sleep_event () ; 
 int /*<<< orphan*/  sched_clock_idle_wakeup_event (int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct cpuidle_device*,TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int us_to_pm_timer_ticks (int) ; 

__attribute__((used)) static int acpi_idle_enter_bm(struct cpuidle_device *dev,
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

	if (!cx->bm_sts_skip && acpi_idle_bm_check()) {
		if (dev->safe_state) {
			dev->last_state = dev->safe_state;
			return dev->safe_state->enter(dev, dev->safe_state);
		} else {
			local_irq_disable();
			acpi_safe_halt();
			local_irq_enable();
			return 0;
		}
	}

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

	acpi_unlazy_tlb(smp_processor_id());

	/* Tell the scheduler that we are going deep-idle: */
	sched_clock_idle_sleep_event();
	/*
	 * Must be done before busmaster disable as we might need to
	 * access HPET !
	 */
	lapic_timer_state_broadcast(pr, cx, 1);

	kt1 = ktime_get_real();
	/*
	 * disable bus master
	 * bm_check implies we need ARB_DIS
	 * !bm_check implies we need cache flush
	 * bm_control implies whether we can do ARB_DIS
	 *
	 * That leaves a case where bm_check is set and bm_control is
	 * not set. In that case we cannot do much, we enter C3
	 * without doing anything.
	 */
	if (pr->flags.bm_check && pr->flags.bm_control) {
		spin_lock(&c3_lock);
		c3_cpu_count++;
		/* Disable bus master arbitration when all CPUs are in C3 */
		if (c3_cpu_count == num_online_cpus())
			acpi_write_bit_register(ACPI_BITREG_ARB_DISABLE, 1);
		spin_unlock(&c3_lock);
	} else if (!pr->flags.bm_check) {
		ACPI_FLUSH_CPU_CACHE();
	}

	acpi_idle_do_entry(cx);

	/* Re-enable bus master arbitration */
	if (pr->flags.bm_check && pr->flags.bm_control) {
		spin_lock(&c3_lock);
		acpi_write_bit_register(ACPI_BITREG_ARB_DISABLE, 0);
		c3_cpu_count--;
		spin_unlock(&c3_lock);
	}
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