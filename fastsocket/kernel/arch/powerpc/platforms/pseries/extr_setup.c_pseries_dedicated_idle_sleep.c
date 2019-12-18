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
struct TYPE_2__ {int idle; int donate_dedicated_cpu; unsigned long wait_state_cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMT_low () ; 
 int /*<<< orphan*/  HMT_medium () ; 
 int /*<<< orphan*/  HMT_very_low () ; 
 int /*<<< orphan*/  SPRN_PURR ; 
 int /*<<< orphan*/  TIF_POLLING_NRFLAG ; 
 unsigned long __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cede_processor () ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_offline (unsigned int) ; 
 TYPE_1__* get_lppaca () ; 
 unsigned long get_tb () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  ppc64_runlatch_off () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  smt_snooze_delay ; 
 unsigned long tb_ticks_per_usec ; 

__attribute__((used)) static void pseries_dedicated_idle_sleep(void)
{ 
	unsigned int cpu = smp_processor_id();
	unsigned long start_snooze;
	unsigned long in_purr, out_purr;

	/*
	 * Indicate to the HV that we are idle. Now would be
	 * a good time to find other work to dispatch.
	 */
	get_lppaca()->idle = 1;
	get_lppaca()->donate_dedicated_cpu = 1;
	in_purr = mfspr(SPRN_PURR);

	/*
	 * We come in with interrupts disabled, and need_resched()
	 * has been checked recently.  If we should poll for a little
	 * while, do so.
	 */
	if (__get_cpu_var(smt_snooze_delay)) {
		start_snooze = get_tb() +
			__get_cpu_var(smt_snooze_delay) * tb_ticks_per_usec;
		local_irq_enable();
		set_thread_flag(TIF_POLLING_NRFLAG);

		while (get_tb() < start_snooze) {
			if (need_resched() || cpu_is_offline(cpu))
				goto out;
			ppc64_runlatch_off();
			HMT_low();
			HMT_very_low();
		}

		HMT_medium();
		clear_thread_flag(TIF_POLLING_NRFLAG);
		smp_mb();
		local_irq_disable();
		if (need_resched() || cpu_is_offline(cpu))
			goto out;
	}

	cede_processor();

out:
	HMT_medium();
	out_purr = mfspr(SPRN_PURR);
	get_lppaca()->wait_state_cycles += out_purr - in_purr;
	get_lppaca()->donate_dedicated_cpu = 0;
	get_lppaca()->idle = 0;
}