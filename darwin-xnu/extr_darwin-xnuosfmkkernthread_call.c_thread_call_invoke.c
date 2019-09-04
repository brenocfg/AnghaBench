#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int /*<<< orphan*/  (* thread_call_func_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_3__ {int /*<<< orphan*/ * thc_call; } ;
struct TYPE_4__ {TYPE_1__ thc_state; } ;

/* Variables and functions */
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __attribute__((noinline))
thread_call_invoke(thread_call_func_t func, thread_call_param_t param0, thread_call_param_t param1, thread_call_t call)
{
	current_thread()->thc_state.thc_call = call;

#if DEVELOPMENT || DEBUG
	KERNEL_DEBUG_CONSTANT(
	                      MACHDBG_CODE(DBG_MACH_SCHED,MACH_CALLOUT) | DBG_FUNC_START,
	                      VM_KERNEL_UNSLIDE(func), VM_KERNEL_ADDRHIDE(param0), VM_KERNEL_ADDRHIDE(param1), 0, 0);
#endif /* DEVELOPMENT || DEBUG */

#if CONFIG_DTRACE
	uint64_t tc_ttd = call->tc_ttd;
	boolean_t is_delayed = call->tc_flags & THREAD_CALL_DELAYED;
	DTRACE_TMR6(thread_callout__start, thread_call_func_t, func, int, 0, int, (tc_ttd >> 32),
	            (unsigned) (tc_ttd & 0xFFFFFFFF), is_delayed, call);
#endif

	(*func)(param0, param1);

#if CONFIG_DTRACE
	DTRACE_TMR6(thread_callout__end, thread_call_func_t, func, int, 0, int, (tc_ttd >> 32),
	            (unsigned) (tc_ttd & 0xFFFFFFFF), is_delayed, call);
#endif

#if DEVELOPMENT || DEBUG
	KERNEL_DEBUG_CONSTANT(
	                      MACHDBG_CODE(DBG_MACH_SCHED,MACH_CALLOUT) | DBG_FUNC_END,
	                      VM_KERNEL_UNSLIDE(func), 0, 0, 0, 0);
#endif /* DEVELOPMENT || DEBUG */

	current_thread()->thc_state.thc_call = NULL;
}