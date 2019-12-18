#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_7__ {scalar_t__ suspend_parked; int sched_flags; scalar_t__ suspend_count; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int THREAD_ABORTSAFE ; 
 int THREAD_WAIT_NOREPORT_USER ; 
 int TH_SFLAG_ABORTED_MASK ; 
 int TH_SFLAG_DEPRESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_wait (scalar_t__*,int) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_suspended ; 
 int /*<<< orphan*/  thread_terminate_self () ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

void
thread_apc_ast(thread_t thread)
{
	thread_mtx_lock(thread);

	assert(thread->suspend_parked == FALSE);

	spl_t s = splsched();
	thread_lock(thread);

	/* TH_SFLAG_POLLDEPRESS is OK to have here */
	assert((thread->sched_flags & TH_SFLAG_DEPRESS) == 0);

	thread->sched_flags &= ~TH_SFLAG_ABORTED_MASK;
	thread_unlock(thread);
	splx(s);

	if (!thread->active) {
		/* Thread is ready to terminate, time to tear it down */
		thread_mtx_unlock(thread);

		thread_terminate_self();
		/*NOTREACHED*/
	}

	/* If we're suspended, go to sleep and wait for someone to wake us up. */
	if (thread->suspend_count > 0) {
		thread->suspend_parked = TRUE;
		assert_wait(&thread->suspend_count,
				THREAD_ABORTSAFE | THREAD_WAIT_NOREPORT_USER);
		thread_mtx_unlock(thread);

		thread_block(thread_suspended);
		/*NOTREACHED*/
	}

	thread_mtx_unlock(thread);
}