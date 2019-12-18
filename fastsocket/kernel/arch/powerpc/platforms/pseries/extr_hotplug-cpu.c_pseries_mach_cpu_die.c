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
typedef  int u8 ;
struct TYPE_2__ {int idle; int donate_dedicated_cpu; int /*<<< orphan*/  shared_proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ CPU_STATE_INACTIVE ; 
 scalar_t__ CPU_STATE_OFFLINE ; 
 scalar_t__ CPU_STATE_ONLINE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extended_cede_processor (int) ; 
 TYPE_1__* get_lppaca () ; 
 scalar_t__ get_preferred_offline_state (unsigned int) ; 
 int /*<<< orphan*/  get_slb_shadow () ; 
 unsigned int hard_smp_processor_id () ; 
 int /*<<< orphan*/  idle_task_exit () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  pseries_suspend_cpu () ; 
 int /*<<< orphan*/  rtas_stop_self () ; 
 int /*<<< orphan*/  set_cpu_current_state (unsigned int,scalar_t__) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  start_secondary_resume () ; 
 int /*<<< orphan*/  unregister_slb_shadow (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xics_teardown_cpu () ; 

__attribute__((used)) static void pseries_mach_cpu_die(void)
{
	unsigned int cpu = smp_processor_id();
	unsigned int hwcpu = hard_smp_processor_id();
	u8 cede_latency_hint = 0;

	local_irq_disable();
	idle_task_exit();
	xics_teardown_cpu();

	if (get_preferred_offline_state(cpu) == CPU_STATE_INACTIVE) {
		set_cpu_current_state(cpu, CPU_STATE_INACTIVE);
		pseries_suspend_cpu();

		cede_latency_hint = 2;

		get_lppaca()->idle = 1;
		if (!get_lppaca()->shared_proc)
			get_lppaca()->donate_dedicated_cpu = 1;

		while (get_preferred_offline_state(cpu) == CPU_STATE_INACTIVE) {
			extended_cede_processor(cede_latency_hint);
		}

		if (!get_lppaca()->shared_proc)
			get_lppaca()->donate_dedicated_cpu = 0;
		get_lppaca()->idle = 0;

		if (get_preferred_offline_state(cpu) == CPU_STATE_ONLINE) {
			unregister_slb_shadow(hwcpu, __pa(get_slb_shadow()));

			/*
			 * Call to start_secondary_resume() will not return.
			 * Kernel stack will be reset and start_secondary()
			 * will be called to continue the online operation.
			 */
			start_secondary_resume();
		}
	}

	/* Requested state is CPU_STATE_OFFLINE at this point */
	WARN_ON(get_preferred_offline_state(cpu) != CPU_STATE_OFFLINE);

	set_cpu_current_state(cpu, CPU_STATE_OFFLINE);
	unregister_slb_shadow(hwcpu, __pa(get_slb_shadow()));
	rtas_stop_self();

	/* Should never get here... */
	BUG();
	for(;;);
}