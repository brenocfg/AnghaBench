#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* workq_threadreq_t ;
struct TYPE_11__ {scalar_t__ trp_value; int trp_flags; int trp_pri; int trp_pol; } ;
typedef  TYPE_4__ workq_threadreq_param_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ thread_qos_t ;
struct workqueue {int wq_event_manager_priority; } ;
struct TYPE_8__ {scalar_t__ workloop_params; scalar_t__ qos; } ;
struct TYPE_9__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {int /*<<< orphan*/  uu_workq_flags; TYPE_2__ uu_save; int /*<<< orphan*/  uu_workq_pri; int /*<<< orphan*/  uu_thread; } ;
struct TYPE_10__ {scalar_t__ tr_qos; int tr_flags; } ;

/* Variables and functions */
 int POLICY_TIMESHARE ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int TRP_POLICY ; 
 int TRP_PRIORITY ; 
 int TR_FLAG_WL_PARAMS ; 
 int /*<<< orphan*/  UT_WORKQ_OUTSIDE_QOS ; 
 int /*<<< orphan*/  WORKQ_POLICY_INIT (scalar_t__) ; 
 scalar_t__ WORKQ_THREAD_QOS_CLEANUP ; 
 scalar_t__ WORKQ_THREAD_QOS_MANAGER ; 
 int _PTHREAD_PRIORITY_SCHED_PRI_FLAG ; 
 int _PTHREAD_PRIORITY_SCHED_PRI_MASK ; 
 scalar_t__ _pthread_priority_thread_qos (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ kqueue_threadreq_workloop_param (TYPE_3__*) ; 
 int /*<<< orphan*/  thread_set_workq_pri (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
workq_thread_reset_pri(struct workqueue *wq, struct uthread *uth,
		workq_threadreq_t req)
{
	thread_t th = uth->uu_thread;
	thread_qos_t qos = req ? req->tr_qos : WORKQ_THREAD_QOS_CLEANUP;
	workq_threadreq_param_t trp = { };
	int priority = 31;
	int policy = POLICY_TIMESHARE;

	if (req && (req->tr_flags & TR_FLAG_WL_PARAMS)) {
		trp = kqueue_threadreq_workloop_param(req);
	}

	uth->uu_workq_pri = WORKQ_POLICY_INIT(qos);
	uth->uu_workq_flags &= ~UT_WORKQ_OUTSIDE_QOS;
	uth->uu_save.uus_workq_park_data.workloop_params = trp.trp_value;

	// qos sent out to userspace (may differ from uu_workq_pri on param threads)
	uth->uu_save.uus_workq_park_data.qos = qos;

	if (qos == WORKQ_THREAD_QOS_MANAGER) {
		uint32_t mgr_pri = wq->wq_event_manager_priority;
		assert(trp.trp_value == 0); // manager qos and thread policy don't mix

		if (mgr_pri & _PTHREAD_PRIORITY_SCHED_PRI_FLAG) {
			mgr_pri &= _PTHREAD_PRIORITY_SCHED_PRI_MASK;
			thread_set_workq_pri(th, THREAD_QOS_UNSPECIFIED, mgr_pri,
					POLICY_TIMESHARE);
			return;
		}

		qos = _pthread_priority_thread_qos(mgr_pri);
	} else {
		if (trp.trp_flags & TRP_PRIORITY) {
			qos = THREAD_QOS_UNSPECIFIED;
			priority = trp.trp_pri;
			uth->uu_workq_flags |= UT_WORKQ_OUTSIDE_QOS;
		}

		if (trp.trp_flags & TRP_POLICY) {
			policy = trp.trp_pol;
		}
	}

	thread_set_workq_pri(th, qos, priority, policy);
}