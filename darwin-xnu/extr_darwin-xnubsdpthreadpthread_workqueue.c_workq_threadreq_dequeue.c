#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* workq_threadreq_t ;
struct workqueue {TYPE_1__* wq_event_manager_threadreq; int /*<<< orphan*/  wq_reqcount; } ;
struct TYPE_4__ {scalar_t__ tr_count; scalar_t__ tr_qos; int tr_flags; int /*<<< orphan*/  tr_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE ; 
 int TR_FLAG_OVERCOMMIT ; 
 scalar_t__ WORKQ_THREAD_QOS_MANAGER ; 
 int /*<<< orphan*/  _wq_thactive_refresh_best_constrained_req_qos (struct workqueue*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ priority_queue_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_priority_queue_for_req (struct workqueue*,TYPE_1__*) ; 

__attribute__((used)) static bool
workq_threadreq_dequeue(struct workqueue *wq, workq_threadreq_t req)
{
	wq->wq_reqcount--;

	if (--req->tr_count == 0) {
		if (req->tr_qos == WORKQ_THREAD_QOS_MANAGER) {
			assert(wq->wq_event_manager_threadreq == req);
			assert(req->tr_count == 0);
			wq->wq_event_manager_threadreq = NULL;
			return true;
		}
		if (priority_queue_remove(workq_priority_queue_for_req(wq, req),
				&req->tr_entry, PRIORITY_QUEUE_SCHED_PRI_MAX_HEAP_COMPARE)) {
			if ((req->tr_flags & TR_FLAG_OVERCOMMIT) == 0) {
				_wq_thactive_refresh_best_constrained_req_qos(wq);
			}
			return true;
		}
	}
	return false;
}