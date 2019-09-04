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
typedef  TYPE_1__* thread_t ;
struct waitq {scalar_t__ waitq_eventmask; } ;
struct TYPE_6__ {struct waitq* waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_thread_magic (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_clear_waitq_state (TYPE_1__*) ; 
 scalar_t__ waitq_empty (struct waitq*) ; 
 struct waitq* waitq_get_safeq (struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 scalar_t__ waitq_is_global (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock_try (struct waitq*) ; 
 int /*<<< orphan*/  waitq_stats_count_clear_wakeup (struct waitq*) ; 
 int /*<<< orphan*/  waitq_thread_remove (struct waitq*,TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 

int waitq_pull_thread_locked(struct waitq *waitq, thread_t thread)
{
	struct waitq *safeq;

	assert_thread_magic(thread);
	assert(thread->waitq == waitq);

	/* Find the interrupts disabled queue thread is waiting on */
	if (!waitq_irq_safe(waitq)) {
		safeq = waitq_get_safeq(waitq);
	} else {
		safeq = waitq;
	}

	/* thread is already locked so have to try for the waitq lock */
	if (!waitq_lock_try(safeq))
		return 0;

	waitq_thread_remove(safeq, thread);
	thread_clear_waitq_state(thread);
	waitq_stats_count_clear_wakeup(waitq);

	/* clear the global event mask if this was the last thread there! */
	if (waitq_is_global(safeq) && waitq_empty(safeq)) {
		safeq->waitq_eventmask = 0;
		/* JMM - also mark no-waiters on waitq (if not the same as the safeq) */
	}

	waitq_unlock(safeq);

	return 1;
}