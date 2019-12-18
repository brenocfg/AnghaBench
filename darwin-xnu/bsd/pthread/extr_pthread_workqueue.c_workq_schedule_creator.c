#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* workq_threadreq_t ;
struct workqueue {scalar_t__ wq_nthreads; int /*<<< orphan*/  wq_fulfilled; struct uthread* wq_creator; scalar_t__ wq_thidlecount; int /*<<< orphan*/  wq_reqcount; } ;
struct TYPE_7__ {scalar_t__ yields; int /*<<< orphan*/  fulfilled_snapshot; } ;
struct TYPE_8__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {TYPE_2__ uu_save; struct workqueue* uu_thread; } ;
typedef  scalar_t__ proc_t ;
struct TYPE_9__ {int /*<<< orphan*/  tr_qos; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_KEVENT_REDRIVE_THREADREQ ; 
 int DBG_FUNC_NONE ; 
 int TRACE_wq_creator_select ; 
 struct workqueue* TURNSTILE_INHERITOR_NULL ; 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_THREAD ; 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_WORKQ ; 
 int WORKQ_THREADREQ_CAN_CREATE_THREADS ; 
 int WORKQ_THREADREQ_CREATOR_SYNC_UPDATE ; 
 int WORKQ_THREADREQ_CREATOR_TRANSFER ; 
 int WORKQ_THREADREQ_SET_AST_ON_FAILURE ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  act_set_astkevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  thread_tid (struct workqueue*) ; 
 scalar_t__ workq_add_new_idle_thread (scalar_t__,struct workqueue*) ; 
 int /*<<< orphan*/  workq_lock_held (struct workqueue*) ; 
 struct uthread* workq_pop_idle_thread (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_delayed_thread_creation (struct workqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_schedule_immediate_thread_creation (struct workqueue*) ; 
 scalar_t__ workq_thread_needs_priority_change (TYPE_3__*,struct uthread*) ; 
 int /*<<< orphan*/  workq_thread_reset_pri (struct workqueue*,struct uthread*,TYPE_3__*) ; 
 int /*<<< orphan*/  workq_thread_wakeup (struct uthread*) ; 
 TYPE_3__* workq_threadreq_select_for_creator (struct workqueue*) ; 
 int /*<<< orphan*/  workq_turnstile_update_inheritor (struct workqueue*,struct workqueue*,int /*<<< orphan*/ ) ; 
 scalar_t__ wq_max_threads ; 

__attribute__((used)) static void
workq_schedule_creator(proc_t p, struct workqueue *wq, int flags)
{
	workq_threadreq_t req;
	struct uthread *uth;

	workq_lock_held(wq);
	assert(p || (flags & WORKQ_THREADREQ_CAN_CREATE_THREADS) == 0);

again:
	uth = wq->wq_creator;

	if (!wq->wq_reqcount) {
		if (uth == NULL) {
			workq_turnstile_update_inheritor(wq, TURNSTILE_INHERITOR_NULL, 0);
		}
		return;
	}

	req = workq_threadreq_select_for_creator(wq);
	if (req == NULL) {
		if (flags & WORKQ_THREADREQ_CREATOR_SYNC_UPDATE) {
			assert((flags & WORKQ_THREADREQ_CREATOR_TRANSFER) == 0);
			/*
			 * turnstile propagation code is reaching out to us,
			 * and we still don't want to do anything, do not recurse.
			 */
		} else {
			workq_turnstile_update_inheritor(wq, wq, TURNSTILE_INHERITOR_WORKQ);
		}
		return;
	}

	if (uth) {
		/*
		 * We need to maybe override the creator we already have
		 */
		if (workq_thread_needs_priority_change(req, uth)) {
			WQ_TRACE_WQ(TRACE_wq_creator_select | DBG_FUNC_NONE,
					wq, 1, thread_tid(uth->uu_thread), req->tr_qos, 0);
			workq_thread_reset_pri(wq, uth, req);
		}
	} else if (wq->wq_thidlecount) {
		/*
		 * We need to unpark a creator thread
		 */
		wq->wq_creator = uth = workq_pop_idle_thread(wq);
		if (workq_thread_needs_priority_change(req, uth)) {
			workq_thread_reset_pri(wq, uth, req);
		}
		workq_turnstile_update_inheritor(wq, uth->uu_thread,
				TURNSTILE_INHERITOR_THREAD);
		WQ_TRACE_WQ(TRACE_wq_creator_select | DBG_FUNC_NONE,
				wq, 2, thread_tid(uth->uu_thread), req->tr_qos, 0);
		uth->uu_save.uus_workq_park_data.fulfilled_snapshot = wq->wq_fulfilled;
		uth->uu_save.uus_workq_park_data.yields = 0;
		workq_thread_wakeup(uth);
	} else {
		/*
		 * We need to allocate a thread...
		 */
		if (__improbable(wq->wq_nthreads >= wq_max_threads)) {
			/* out of threads, just go away */
		} else if (flags & WORKQ_THREADREQ_SET_AST_ON_FAILURE) {
			act_set_astkevent(current_thread(), AST_KEVENT_REDRIVE_THREADREQ);
		} else if (!(flags & WORKQ_THREADREQ_CAN_CREATE_THREADS)) {
			/* This can drop the workqueue lock, and take it again */
			workq_schedule_immediate_thread_creation(wq);
		} else if (workq_add_new_idle_thread(p, wq)) {
			goto again;
		} else {
			workq_schedule_delayed_thread_creation(wq, 0);
		}

		if (flags & WORKQ_THREADREQ_CREATOR_TRANSFER) {
			/*
			 * workq_schedule_creator() failed at creating a thread,
			 * and the responsibility of redriving is now with a thread-call.
			 *
			 * We still need to tell the turnstile the previous creator is gone.
			 */
			workq_turnstile_update_inheritor(wq, NULL, 0);
		}
	}
}