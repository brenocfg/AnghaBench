#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  (* processor_idle_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;
struct TYPE_4__ {int cpu_signal; int rtcPop; scalar_t__ idle_timer_notify; int idle_timer_deadline; int /*<<< orphan*/  cpu_id; scalar_t__ cpu_idle_notify; int /*<<< orphan*/ * cpu_user_debug; int /*<<< orphan*/  cpu_active_thread; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearIdlePop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSB_SY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlushPoC_Dcache () ; 
 int /*<<< orphan*/  Idle_load_context () ; 
 int /*<<< orphan*/  InvalidatePoU_Icache () ; 
 int SIGPdisabled ; 
 int /*<<< orphan*/  SetIdlePop () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __builtin_arm_dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __builtin_arm_wfi () ; 
 int /*<<< orphan*/  arm64_force_wfi_clock_gate () ; 
 int /*<<< orphan*/  arm_debug_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  clock_delay_until (int) ; 
 int /*<<< orphan*/  cpu_idle_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  cyclone_typhoon_prepare_for_wfi () ; 
 int /*<<< orphan*/  cyclone_typhoon_return_from_wfi () ; 
 int /*<<< orphan*/  flush_core_tlb () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  idle_enable ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kpc_idle () ; 
 int /*<<< orphan*/  mt_cpu_idle (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_cache_idle_enter () ; 
 int /*<<< orphan*/  platform_cache_idle_exit () ; 
 int /*<<< orphan*/  pmap_switch_user_ttb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 
 int wfi ; 
 int wfi_delay ; 
 int wfi_flags ; 

void __attribute__((noreturn))
cpu_idle(void)
{
	cpu_data_t     *cpu_data_ptr = getCpuDatap();
	uint64_t	new_idle_timeout_ticks = 0x0ULL, lastPop;

	if ((!idle_enable) || (cpu_data_ptr->cpu_signal & SIGPdisabled))
		Idle_load_context();
	if (!SetIdlePop())
		Idle_load_context();
	lastPop = cpu_data_ptr->rtcPop;

	pmap_switch_user_ttb(kernel_pmap);
	cpu_data_ptr->cpu_active_thread = current_thread();
	if (cpu_data_ptr->cpu_user_debug)
		arm_debug_set(NULL);
	cpu_data_ptr->cpu_user_debug = NULL;

	if (cpu_data_ptr->cpu_idle_notify)
		((processor_idle_t) cpu_data_ptr->cpu_idle_notify) (cpu_data_ptr->cpu_id, TRUE, &new_idle_timeout_ticks);

	if (cpu_data_ptr->idle_timer_notify != 0) {
		if (new_idle_timeout_ticks == 0x0ULL) {
			/* turn off the idle timer */
			cpu_data_ptr->idle_timer_deadline = 0x0ULL;
		} else {
			/* set the new idle timeout */
			clock_absolutetime_interval_to_deadline(new_idle_timeout_ticks, &cpu_data_ptr->idle_timer_deadline);
		}
		timer_resync_deadlines();
		if (cpu_data_ptr->rtcPop != lastPop)
			SetIdlePop();
	}

#if KPC
	kpc_idle();
#endif
#if MONOTONIC
	mt_cpu_idle(cpu_data_ptr);
#endif /* MONOTONIC */

	if (wfi) {
		platform_cache_idle_enter();

#if DEVELOPMENT || DEBUG
		// When simulating wfi overhead,
		// force wfi to clock gating only
		if (wfi == 2) {
			arm64_force_wfi_clock_gate();
		}
#endif /* DEVELOPMENT || DEBUG */

#if defined(APPLECYCLONE) || defined(APPLETYPHOON)
		// <rdar://problem/15827409> CPU1 Stuck in WFIWT Because of MMU Prefetch
		cyclone_typhoon_prepare_for_wfi();
#endif
		__builtin_arm_dsb(DSB_SY);
		__builtin_arm_wfi();

#if defined(APPLECYCLONE) || defined(APPLETYPHOON)
		// <rdar://problem/15827409> CPU1 Stuck in WFIWT Because of MMU Prefetch
		cyclone_typhoon_return_from_wfi();
#endif

#if DEVELOPMENT || DEBUG
		// Handle wfi overhead simulation
		if (wfi == 2) {
			uint64_t deadline;

			// Calculate wfi delay deadline
			clock_absolutetime_interval_to_deadline(wfi_delay, &deadline);

			// Flush L1 caches
			if ((wfi_flags & 1) != 0) {
				InvalidatePoU_Icache();
				FlushPoC_Dcache();
			}

			// Flush TLBs
			if ((wfi_flags & 2) != 0) {
				flush_core_tlb();
			}

			// Wait for the ballance of the wfi delay
			clock_delay_until(deadline);
		}
#endif /* DEVELOPMENT || DEBUG */

		platform_cache_idle_exit();
	}

	ClearIdlePop(TRUE);

	cpu_idle_exit(FALSE);
}