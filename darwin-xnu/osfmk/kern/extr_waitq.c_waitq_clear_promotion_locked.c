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
typedef  TYPE_1__* thread_t ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_8__ {int sched_flags; } ;

/* Variables and functions */
 TYPE_1__* THREAD_NULL ; 
 int TH_SFLAG_WAITQ_PROMOTED ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  sched_thread_unpromote_reason (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int waitq_held (struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 

void waitq_clear_promotion_locked(struct waitq *waitq, thread_t thread)
{
	spl_t s;

	assert(waitq_held(waitq));
	assert(thread != THREAD_NULL);
	assert(thread == current_thread());

	/* This flag is only cleared by the thread itself, so safe to check outside lock */
	if ((thread->sched_flags & TH_SFLAG_WAITQ_PROMOTED) != TH_SFLAG_WAITQ_PROMOTED)
		return;

	if (!waitq_irq_safe(waitq))
		s = splsched();
	thread_lock(thread);

	sched_thread_unpromote_reason(thread, TH_SFLAG_WAITQ_PROMOTED, 0);

	thread_unlock(thread);
	if (!waitq_irq_safe(waitq))
		splx(s);
}