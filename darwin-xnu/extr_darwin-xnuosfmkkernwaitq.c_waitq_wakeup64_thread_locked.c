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
typedef  int /*<<< orphan*/  thread_t ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event64_t ;

/* Variables and functions */
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ WAITQ_UNLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_thread_magic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_go (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 int waitq_held (struct waitq*) ; 
 scalar_t__ waitq_select_thread_locked (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_stats_count_fail (struct waitq*) ; 
 int /*<<< orphan*/  waitq_stats_count_wakeup (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 

kern_return_t waitq_wakeup64_thread_locked(struct waitq *waitq,
					   event64_t wake_event,
					   thread_t thread,
					   wait_result_t result,
					   waitq_lock_state_t lock_state)
{
	kern_return_t ret;
	spl_t th_spl;

	assert(waitq_held(waitq));
	assert_thread_magic(thread);

	/*
	 * See if the thread was still waiting there.  If so, it got
	 * dequeued and returned locked.
	 */
	ret = waitq_select_thread_locked(waitq, wake_event, thread, &th_spl);

	if (ret == KERN_SUCCESS)
		waitq_stats_count_wakeup(waitq);
	else
		waitq_stats_count_fail(waitq);

	if (lock_state == WAITQ_UNLOCK)
		waitq_unlock(waitq);

	if (ret != KERN_SUCCESS)
		return KERN_NOT_WAITING;

	ret = thread_go(thread, result);
	assert(ret == KERN_SUCCESS);
	thread_unlock(thread);
	splx(th_spl);

	return ret;
}