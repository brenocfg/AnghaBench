#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ waitq_lock_state_t ;
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ thread_t ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event64_t ;

/* Variables and functions */
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ THREAD_NULL ; 
 int WAITQ_SELECT_MAX_PRI ; 
 scalar_t__ WAITQ_UNLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  maybe_adjust_thread_pri (scalar_t__,int,struct waitq*) ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_go (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (scalar_t__) ; 
 int waitq_held (struct waitq*) ; 
 scalar_t__ waitq_select_max_locked (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ waitq_select_one_locked (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_stats_count_fail (struct waitq*) ; 
 int /*<<< orphan*/  waitq_stats_count_wakeup (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 

kern_return_t waitq_wakeup64_one_locked(struct waitq *waitq,
					event64_t wake_event,
					wait_result_t result,
					uint64_t *reserved_preposts,
					int priority,
					waitq_lock_state_t lock_state)
{
	thread_t thread;
	spl_t th_spl;

	assert(waitq_held(waitq));

	if (priority == WAITQ_SELECT_MAX_PRI) {
		thread = waitq_select_max_locked(waitq, wake_event,
		                                 reserved_preposts,
		                                 &th_spl);
	} else {
		thread = waitq_select_one_locked(waitq, wake_event,
		                                 reserved_preposts,
		                                 priority, &th_spl);
	}


	if (thread != THREAD_NULL)
		waitq_stats_count_wakeup(waitq);
	else
		waitq_stats_count_fail(waitq);

	if (lock_state == WAITQ_UNLOCK)
		waitq_unlock(waitq);

	if (thread != THREAD_NULL) {
		maybe_adjust_thread_pri(thread, priority, waitq);
		kern_return_t ret = thread_go(thread, result);
		assert(ret == KERN_SUCCESS);
		thread_unlock(thread);
		splx(th_spl);
		return ret;
	}

	return KERN_NOT_WAITING;
}