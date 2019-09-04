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
struct workqueue {scalar_t__ wq_reqcount; int /*<<< orphan*/  wq_nthreads; int /*<<< orphan*/  wq_thidlecount; int /*<<< orphan*/  wq_thrunlist; } ;
struct uthread {int uu_workq_flags; int /*<<< orphan*/  uu_thread; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct uthread*,int /*<<< orphan*/ ) ; 
 int TRACE_wq_thread_terminate ; 
 int UT_WORKQ_DYING ; 
 int /*<<< orphan*/  WORKQ_THREADREQ_CAN_CREATE_THREADS ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct workqueue* proc_get_wqptr_fast (struct proc*) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_workq_entry ; 
 int /*<<< orphan*/  workq_death_policy_evaluate (struct workqueue*,int) ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_creator (struct proc*,struct workqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 
 scalar_t__ wq_max_threads ; 

void
workq_thread_terminate(struct proc *p, struct uthread *uth)
{
	struct workqueue *wq = proc_get_wqptr_fast(p);

	workq_lock_spin(wq);
	TAILQ_REMOVE(&wq->wq_thrunlist, uth, uu_workq_entry);
	if (uth->uu_workq_flags & UT_WORKQ_DYING) {
		WQ_TRACE_WQ(TRACE_wq_thread_terminate | DBG_FUNC_END,
				wq, wq->wq_thidlecount, 0, 0, 0);
		workq_death_policy_evaluate(wq, 1);
	}
	if (wq->wq_nthreads-- == wq_max_threads) {
		/*
		 * We got under the thread limit again, which may have prevented
		 * thread creation from happening, redrive if there are pending requests
		 */
		if (wq->wq_reqcount) {
			workq_schedule_creator(p, wq, WORKQ_THREADREQ_CAN_CREATE_THREADS);
		}
	}
	workq_unlock(wq);

	thread_deallocate(uth->uu_thread);
}