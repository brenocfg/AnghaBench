#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wait_result_t ;
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  TYPE_1__* thread_t ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_6__ {int state; scalar_t__ started; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_EVENT64_T (int /*<<< orphan*/ ) ; 
 scalar_t__ THREAD_WAITING ; 
 int TH_UNINT ; 
 int TH_WAIT ; 
 int /*<<< orphan*/  TIMEOUT_NO_LEEWAY ; 
 int /*<<< orphan*/  TIMEOUT_URGENCY_SYS_NORMAL ; 
 int /*<<< orphan*/  TIMEOUT_WAIT_FOREVER ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct waitq* assert_wait_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 scalar_t__ waitq_assert_wait64_locked (struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 

void
thread_start_in_assert_wait(
	thread_t			thread,
	event_t             event,
	wait_interrupt_t    interruptible)
{
	struct waitq *waitq = assert_wait_queue(event);
	wait_result_t wait_result;
	spl_t spl;

	spl = splsched();
	waitq_lock(waitq);

	/* clear out startup condition (safe because thread not started yet) */
	thread_lock(thread);
	assert(!thread->started);
	assert((thread->state & (TH_WAIT | TH_UNINT)) == (TH_WAIT | TH_UNINT));
	thread->state &= ~(TH_WAIT | TH_UNINT);
	thread_unlock(thread);

	/* assert wait interruptibly forever */
	wait_result = waitq_assert_wait64_locked(waitq, CAST_EVENT64_T(event),
	                                 interruptible,
	                                 TIMEOUT_URGENCY_SYS_NORMAL,
	                                 TIMEOUT_WAIT_FOREVER,
	                                 TIMEOUT_NO_LEEWAY,
	                                 thread);
	assert (wait_result == THREAD_WAITING);

	/* mark thread started while we still hold the waitq lock */
	thread_lock(thread);
	thread->started = TRUE;
	thread_unlock(thread);

	waitq_unlock(waitq);
	splx(spl);
}