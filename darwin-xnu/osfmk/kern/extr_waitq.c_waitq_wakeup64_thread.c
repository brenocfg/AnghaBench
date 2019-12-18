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
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event64_t ;

/* Variables and functions */
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,struct waitq*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_go (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 scalar_t__ waitq_select_thread_locked (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_stats_count_fail (struct waitq*) ; 
 int /*<<< orphan*/  waitq_stats_count_wakeup (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 

kern_return_t waitq_wakeup64_thread(struct waitq *waitq,
				    event64_t wake_event,
				    thread_t thread,
				    wait_result_t result)
{
	kern_return_t ret;
	spl_t s, th_spl;

	if (!waitq_valid(waitq))
		panic("Invalid waitq: %p", waitq);

	if (waitq_irq_safe(waitq))
		s = splsched();
	waitq_lock(waitq);

	ret = waitq_select_thread_locked(waitq, wake_event, thread, &th_spl);
	/* on success, returns 'thread' locked */

	waitq_unlock(waitq);

	if (ret == KERN_SUCCESS) {
		ret = thread_go(thread, result);
		assert(ret == KERN_SUCCESS);
		thread_unlock(thread);
		splx(th_spl);
		waitq_stats_count_wakeup(waitq);
	} else {
		ret = KERN_NOT_WAITING;
		waitq_stats_count_fail(waitq);
	}

	if (waitq_irq_safe(waitq))
		splx(s);

	return ret;
}