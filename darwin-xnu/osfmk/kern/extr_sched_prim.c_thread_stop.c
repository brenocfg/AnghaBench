#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wait_result_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  processor_t ;
typedef  void* boolean_t ;
struct TYPE_9__ {int state; void* wake_active; int /*<<< orphan*/  chosen_processor; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 scalar_t__ THREAD_AWAKENED ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 scalar_t__ THREAD_WAITING ; 
 int TH_RUN ; 
 int TH_SUSP ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ assert_wait (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cause_ast_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_block (int /*<<< orphan*/ ) ; 
 void* thread_isoncpu (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unstop (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_unlock (TYPE_1__*) ; 

boolean_t
thread_stop(
	thread_t		thread,
	boolean_t	until_not_runnable)
{
	wait_result_t	wresult;
	spl_t			s = splsched();
	boolean_t		oncpu;

	wake_lock(thread);
	thread_lock(thread);

	while (thread->state & TH_SUSP) {
		thread->wake_active = TRUE;
		thread_unlock(thread);

		wresult = assert_wait(&thread->wake_active, THREAD_ABORTSAFE);
		wake_unlock(thread);
		splx(s);

		if (wresult == THREAD_WAITING)
			wresult = thread_block(THREAD_CONTINUE_NULL);

		if (wresult != THREAD_AWAKENED)
			return (FALSE);

		s = splsched();
		wake_lock(thread);
		thread_lock(thread);
	}

	thread->state |= TH_SUSP;

	while ((oncpu = thread_isoncpu(thread)) ||
		   (until_not_runnable && (thread->state & TH_RUN))) {
		processor_t		processor;
		
		if (oncpu) {
			assert(thread->state & TH_RUN);
			processor = thread->chosen_processor;
			cause_ast_check(processor);
		}

		thread->wake_active = TRUE;
		thread_unlock(thread);

		wresult = assert_wait(&thread->wake_active, THREAD_ABORTSAFE);
		wake_unlock(thread);
		splx(s);

		if (wresult == THREAD_WAITING)
			wresult = thread_block(THREAD_CONTINUE_NULL);

		if (wresult != THREAD_AWAKENED) {
			thread_unstop(thread);
			return (FALSE);
		}

		s = splsched();
		wake_lock(thread);
		thread_lock(thread);
	}

	thread_unlock(thread);
	wake_unlock(thread);
	splx(s);
	
	/*
	 * We return with the thread unlocked. To prevent it from
	 * transitioning to a runnable state (or from TH_RUN to
	 * being on the CPU), the caller must ensure the thread
	 * is stopped via an external means (such as an AST)
	 */

	return (TRUE);
}