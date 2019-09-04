#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wait_result_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  processor_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int state; int /*<<< orphan*/  wake_active; int /*<<< orphan*/  chosen_processor; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ THREAD_WAITING ; 
 int TH_RUN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ assert_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cause_ast_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_isoncpu (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_unlock (TYPE_1__*) ; 

void
thread_wait(
	thread_t	thread,
	boolean_t	until_not_runnable)
{
	wait_result_t	wresult;
	boolean_t 	oncpu;
	processor_t	processor;
	spl_t		s = splsched();

	wake_lock(thread);
	thread_lock(thread);

	/*
	 * Wait until not running on a CPU.  If stronger requirement
	 * desired, wait until not runnable.  Assumption: if thread is
	 * on CPU, then TH_RUN is set, so we're not waiting in any case
	 * where the original, pure "TH_RUN" check would have let us 
	 * finish.
	 */
	while ((oncpu = thread_isoncpu(thread)) ||
			(until_not_runnable && (thread->state & TH_RUN))) {

		if (oncpu) {
			assert(thread->state & TH_RUN);
			processor = thread->chosen_processor;
			cause_ast_check(processor);
		}

		thread->wake_active = TRUE;
		thread_unlock(thread);

		wresult = assert_wait(&thread->wake_active, THREAD_UNINT);
		wake_unlock(thread);
		splx(s);

		if (wresult == THREAD_WAITING)
			thread_block(THREAD_CONTINUE_NULL);

		s = splsched();
		wake_lock(thread);
		thread_lock(thread);
	}

	thread_unlock(thread);
	wake_unlock(thread);
	splx(s);
}