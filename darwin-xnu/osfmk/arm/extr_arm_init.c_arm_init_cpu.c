#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cpu_CLW_active; int cpu_number; TYPE_1__* cpu_processor; int /*<<< orphan*/  rtcPop; int /*<<< orphan*/  cpu_active_thread; int /*<<< orphan*/  cpu_flags; } ;
typedef  TYPE_2__ cpu_data_t ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_id; } ;

/* Variables and functions */
 TYPE_2__ BootCpuData ; 
 int DAIFSC_ASYNCF ; 
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PE_arm_debug_enable_trace () ; 
 int /*<<< orphan*/  PE_init_platform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SCTLR_PREDIC ; 
 int /*<<< orphan*/  SleepState ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __builtin_arm_wsr (char*,int) ; 
 int /*<<< orphan*/  arm64_stall_sleep ; 
 int arm_diag ; 
 int /*<<< orphan*/  bootprofile_wake_from_sleep () ; 
 int /*<<< orphan*/  commpage_update_timebase () ; 
 int /*<<< orphan*/  cpu_defeatures_set (int) ; 
 int /*<<< orphan*/  cpu_init () ; 
 int /*<<< orphan*/  cpu_machine_idle_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_timebase_init (int /*<<< orphan*/ ) ; 
 int cpus_defeatures ; 
 int /*<<< orphan*/  fiq_context_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_mmu_tlb () ; 
 int get_mmu_control () ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_set_current_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_wake_per_core () ; 
 int /*<<< orphan*/  pmap_clear_user_ttb () ; 
 int /*<<< orphan*/  serial_init () ; 
 int /*<<< orphan*/  set_mmu_control (int) ; 
 int /*<<< orphan*/  slave_main (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 

void
arm_init_cpu(
	cpu_data_t	*cpu_data_ptr)
{
#if __ARM_PAN_AVAILABLE__
	__builtin_arm_wsr("pan", 1);
#endif

	cpu_data_ptr->cpu_flags &= ~SleepState;
#if     __ARM_SMP__ && defined(ARMA7)
	cpu_data_ptr->cpu_CLW_active = 1;
#endif

	machine_set_current_thread(cpu_data_ptr->cpu_active_thread);

#if __arm64__
	pmap_clear_user_ttb();
	flush_mmu_tlb();
	/* Enable asynchronous exceptions */
	__builtin_arm_wsr("DAIFClr", DAIFSC_ASYNCF);
#endif

	cpu_machine_idle_init(FALSE);

	cpu_init();

#if	(__ARM_ARCH__ == 7)
	if (arm_diag & 0x8000)
		set_mmu_control((get_mmu_control()) ^ SCTLR_PREDIC);
#endif
#ifdef	APPLETYPHOON
	if ((cpus_defeatures & (0xF << 4*cpu_data_ptr->cpu_number)) != 0)
		cpu_defeatures_set((cpus_defeatures >> 4*cpu_data_ptr->cpu_number) & 0xF);
#endif
	/* Initialize the timebase before serial_init, as some serial
	 * drivers use mach_absolute_time() to implement rate control
	 */
	cpu_timebase_init(FALSE);

	if (cpu_data_ptr == &BootCpuData) {
#if __arm64__ && __ARM_GLOBAL_SLEEP_BIT__
		/*
		 * Prevent CPUs from going into deep sleep until all
		 * CPUs are ready to do so.
		 */
		arm64_stall_sleep = TRUE;
#endif
		serial_init();
		PE_init_platform(TRUE, NULL);
		commpage_update_timebase();
	}

	fiq_context_init(TRUE);
	cpu_data_ptr->rtcPop = EndOfAllTime;
	timer_resync_deadlines();

#if DEVELOPMENT || DEBUG
	PE_arm_debug_enable_trace();
#endif

	kprintf("arm_cpu_init(): cpu %d online\n", cpu_data_ptr->cpu_processor->cpu_id);

	if (cpu_data_ptr == &BootCpuData) {
#if CONFIG_TELEMETRY
		bootprofile_wake_from_sleep();
#endif /* CONFIG_TELEMETRY */
	}
#if MONOTONIC && defined(__arm64__)
	mt_wake_per_core();
#endif /* MONOTONIC && defined(__arm64__) */


	slave_main(NULL);
}