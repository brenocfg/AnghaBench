#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* workq_threadreq_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ thread_qos_t ;
struct workqueue {scalar_t__ wq_nthreads; int /*<<< orphan*/  wq_constrained_threads_scheduled; int /*<<< orphan*/  wq_fulfilled; int /*<<< orphan*/ * wq_thscheduled_count; scalar_t__ wq_thidlecount; } ;
struct TYPE_9__ {TYPE_3__* thread_request; scalar_t__ upcall_flags; } ;
struct TYPE_10__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {TYPE_2__ uu_save; int /*<<< orphan*/  uu_workq_flags; } ;
struct proc {int dummy; } ;
typedef  int pthread_priority_t ;
struct TYPE_11__ {int tr_flags; int tr_qos; scalar_t__ tr_count; int /*<<< orphan*/  tr_state; int /*<<< orphan*/  tr_entry; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int ECANCELED ; 
 int EINVAL ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int TRACE_wq_thread_request_initiate ; 
 int TRACE_wq_wqops_reqthreads ; 
 int TR_FLAG_OVERCOMMIT ; 
 int TR_FLAG_WL_PARAMS ; 
 int /*<<< orphan*/  TR_STATE_NEW ; 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  UT_WORKQ_EARLY_BOUND ; 
 int /*<<< orphan*/  UT_WORKQ_OVERCOMMIT ; 
 int /*<<< orphan*/  WORKQ_THREADREQ_CAN_CREATE_THREADS ; 
 scalar_t__ WQ_FLAG_THREAD_NEWSPI ; 
 scalar_t__ WQ_FLAG_THREAD_OVERCOMMIT ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int _PTHREAD_PRIORITY_OVERCOMMIT_FLAG ; 
 scalar_t__ _pthread_priority_thread_qos (int) ; 
 size_t _wq_bucket (scalar_t__) ; 
 scalar_t__ _wq_exiting (struct workqueue*) ; 
 int /*<<< orphan*/  _wq_thactive_inc (struct workqueue*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  priority_queue_entry_init (int /*<<< orphan*/ *) ; 
 struct workqueue* proc_get_wqptr (struct proc*) ; 
 scalar_t__ workq_add_new_idle_thread (struct proc*,struct workqueue*) ; 
 scalar_t__ workq_constrained_allowance (struct workqueue*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 struct uthread* workq_pop_idle_thread (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_creator (struct proc*,struct workqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_thread_reset_pri (struct workqueue*,struct uthread*,TYPE_3__*) ; 
 int /*<<< orphan*/  workq_thread_wakeup (struct uthread*) ; 
 scalar_t__ workq_threadreq_enqueue (struct workqueue*,TYPE_3__*) ; 
 scalar_t__ workq_trace_req_id (TYPE_3__*) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 
 int /*<<< orphan*/  workq_zone_threadreq ; 
 scalar_t__ wq_max_threads ; 
 TYPE_3__* zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int
workq_reqthreads(struct proc *p, uint32_t reqcount, pthread_priority_t pp)
{
	thread_qos_t qos = _pthread_priority_thread_qos(pp);
	struct workqueue *wq = proc_get_wqptr(p);
	uint32_t unpaced, upcall_flags = WQ_FLAG_THREAD_NEWSPI;

	if (wq == NULL || reqcount <= 0 || reqcount > UINT16_MAX ||
			qos == THREAD_QOS_UNSPECIFIED) {
		return EINVAL;
	}

	WQ_TRACE_WQ(TRACE_wq_wqops_reqthreads | DBG_FUNC_NONE,
			wq, reqcount, pp, 0, 0);

	workq_threadreq_t req = zalloc(workq_zone_threadreq);
	priority_queue_entry_init(&req->tr_entry);
	req->tr_state = TR_STATE_NEW;
	req->tr_flags = 0;
	req->tr_qos   = qos;

	if (pp & _PTHREAD_PRIORITY_OVERCOMMIT_FLAG) {
		req->tr_flags |= TR_FLAG_OVERCOMMIT;
		upcall_flags |= WQ_FLAG_THREAD_OVERCOMMIT;
	}

	WQ_TRACE_WQ(TRACE_wq_thread_request_initiate | DBG_FUNC_NONE,
			wq, workq_trace_req_id(req), req->tr_qos, reqcount, 0);

	workq_lock_spin(wq);
	do {
		if (_wq_exiting(wq)) {
			goto exiting;
		}

		/*
		 * When userspace is asking for parallelism, wakeup up to (reqcount - 1)
		 * threads without pacing, to inform the scheduler of that workload.
		 *
		 * The last requests, or the ones that failed the admission checks are
		 * enqueued and go through the regular creator codepath.
		 *
		 * If there aren't enough threads, add one, but re-evaluate everything
		 * as conditions may now have changed.
		 */
		if (reqcount > 1 && (req->tr_flags & TR_FLAG_OVERCOMMIT) == 0) {
			unpaced = workq_constrained_allowance(wq, qos, NULL, false);
			if (unpaced >= reqcount - 1) {
				unpaced = reqcount - 1;
			}
		} else {
			unpaced = reqcount - 1;
		}

		/*
		 * This path does not currently handle custom workloop parameters
		 * when creating threads for parallelism.
		 */
		assert(!(req->tr_flags & TR_FLAG_WL_PARAMS));

		/*
		 * This is a trimmed down version of workq_threadreq_bind_and_unlock()
		 */
		while (unpaced > 0 && wq->wq_thidlecount) {
			struct uthread *uth = workq_pop_idle_thread(wq);

			_wq_thactive_inc(wq, qos);
			wq->wq_thscheduled_count[_wq_bucket(qos)]++;
			workq_thread_reset_pri(wq, uth, req);
			wq->wq_fulfilled++;

			uth->uu_workq_flags |= UT_WORKQ_EARLY_BOUND;
			if ((req->tr_flags & TR_FLAG_OVERCOMMIT) == 0) {
				uth->uu_workq_flags &= ~UT_WORKQ_OVERCOMMIT;
				wq->wq_constrained_threads_scheduled++;
			}
			uth->uu_save.uus_workq_park_data.upcall_flags = upcall_flags;
			uth->uu_save.uus_workq_park_data.thread_request = req;
			workq_thread_wakeup(uth);
			unpaced--;
			reqcount--;
		}
	} while (unpaced && wq->wq_nthreads < wq_max_threads &&
			workq_add_new_idle_thread(p, wq));

	if (_wq_exiting(wq)) {
		goto exiting;
	}

	req->tr_count = reqcount;
	if (workq_threadreq_enqueue(wq, req)) {
		/* This can drop the workqueue lock, and take it again */
		workq_schedule_creator(p, wq, WORKQ_THREADREQ_CAN_CREATE_THREADS);
	}
	workq_unlock(wq);
	return 0;

exiting:
	workq_unlock(wq);
	zfree(workq_zone_threadreq, req);
	return ECANCELED;
}