#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int wait_result_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/ * thread_continue_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_12__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_SCHED_THREAD_SWITCH ; 
 TYPE_1__* THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int thread_block_parameter (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  thread_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_deallocate_safe (TYPE_1__*) ; 
 int thread_run (TYPE_1__*,int /*<<< orphan*/ *,void*,TYPE_1__*) ; 
 TYPE_1__* thread_run_queue_remove_for_handoff (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 

__attribute__((used)) static wait_result_t
thread_handoff_internal(thread_t thread, thread_continue_t continuation,
		void *parameter)
{
	thread_t deallocate_thread = THREAD_NULL;
	thread_t self = current_thread();

	/*
	 * Try to handoff if supplied.
	 */
	if (thread != THREAD_NULL) {
		spl_t s = splsched();

		thread_t pulled_thread = thread_run_queue_remove_for_handoff(thread);

		KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED,MACH_SCHED_THREAD_SWITCH)|DBG_FUNC_NONE,
				      thread_tid(thread), thread->state,
				      pulled_thread ? TRUE : FALSE, 0, 0);

		if (pulled_thread != THREAD_NULL) {
			if (continuation == NULL) {
				/* We can't be dropping the last ref here */
				thread_deallocate_safe(thread);
			}

			int result = thread_run(self, continuation, parameter, pulled_thread);

			splx(s);
			return result;
		}

		splx(s);

		deallocate_thread = thread;
		thread = THREAD_NULL;
	}

	int result = thread_block_parameter(continuation, parameter);
	if (deallocate_thread != THREAD_NULL) {
		thread_deallocate(deallocate_thread);
	}

	return result;
}