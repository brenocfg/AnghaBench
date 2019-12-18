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
struct cpuidle_state {unsigned long long time; int /*<<< orphan*/  usage; scalar_t__ (* enter ) (struct cpuidle_device*,struct cpuidle_state*) ;} ;
struct cpuidle_device {scalar_t__ last_residency; struct cpuidle_state* last_state; struct cpuidle_state* states; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int (* select ) (struct cpuidle_device*) ;int /*<<< orphan*/  (* reflect ) (struct cpuidle_device*) ;} ;

/* Variables and functions */
 struct cpuidle_device* __get_cpu_var (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpuidle_curr_governor ; 
 int /*<<< orphan*/  cpuidle_devices ; 
 int /*<<< orphan*/  default_idle () ; 
 int /*<<< orphan*/  hrtimer_peek_ahead_timers () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  pm_idle_old () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int stub1 (struct cpuidle_device*) ; 
 scalar_t__ stub2 (struct cpuidle_device*,struct cpuidle_state*) ; 
 int /*<<< orphan*/  stub3 (struct cpuidle_device*) ; 
 int /*<<< orphan*/  trace_power_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuidle_idle_call(void)
{
	struct cpuidle_device *dev = __get_cpu_var(cpuidle_devices);
	struct cpuidle_state *target_state;
	int next_state;

	/* check if the device is ready */
	if (!dev || !dev->enabled) {
		if (pm_idle_old)
			pm_idle_old();
		else
#if defined(CONFIG_ARCH_HAS_DEFAULT_IDLE)
			default_idle();
#else
			local_irq_enable();
#endif
		return;
	}

#if 0
	/* shows regressions, re-enable for 2.6.29 */
	/*
	 * run any timers that can be run now, at this point
	 * before calculating the idle duration etc.
	 */
	hrtimer_peek_ahead_timers();
#endif
	/* ask the governor for the next state */
	next_state = cpuidle_curr_governor->select(dev);
	if (need_resched()) {
		local_irq_enable();
		return;
	}

	target_state = &dev->states[next_state];

	/* enter the state and update stats */
	dev->last_state = target_state;
	dev->last_residency = target_state->enter(dev, target_state);
	if (dev->last_state)
		target_state = dev->last_state;

	target_state->time += (unsigned long long)dev->last_residency;
	target_state->usage++;

	/* give the governor an opportunity to reflect on the outcome */
	if (cpuidle_curr_governor->reflect)
		cpuidle_curr_governor->reflect(dev);
	trace_power_end(smp_processor_id());
}