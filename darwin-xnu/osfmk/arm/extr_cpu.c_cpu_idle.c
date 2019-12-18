#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  (* processor_idle_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;
struct TYPE_3__ {int cpu_signal; int rtcPop; scalar_t__ idle_timer_notify; int idle_timer_deadline; int /*<<< orphan*/  cpu_id; scalar_t__ cpu_idle_notify; int /*<<< orphan*/ * cpu_user_debug; int /*<<< orphan*/  cpu_active_thread; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearIdlePop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Idle_load_context () ; 
 int SIGPdisabled ; 
 int /*<<< orphan*/  SetIdlePop () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arm_debug_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  cpu_idle_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_idle_wfi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  idle_enable ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kpc_idle () ; 
 int /*<<< orphan*/  platform_cache_idle_enter () ; 
 int /*<<< orphan*/  platform_cache_idle_exit () ; 
 int /*<<< orphan*/  pmap_switch_user_ttb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 
 scalar_t__ wfi_fast ; 

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

	platform_cache_idle_enter();
	cpu_idle_wfi((boolean_t) wfi_fast);
	platform_cache_idle_exit();

	ClearIdlePop(TRUE);
	cpu_idle_exit(FALSE);
}