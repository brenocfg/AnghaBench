#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* workq_threadreq_t ;
struct workqueue {int dummy; } ;
struct uthread {int dummy; } ;
struct TYPE_3__ {scalar_t__ tr_qos; int tr_flags; } ;

/* Variables and functions */
 int TR_FLAG_OVERCOMMIT ; 
 scalar_t__ WORKQ_THREAD_QOS_MANAGER ; 
 int workq_constrained_allowance (struct workqueue*,scalar_t__,struct uthread*,int) ; 
 int workq_may_start_event_mgr_thread (struct workqueue*,struct uthread*) ; 

__attribute__((used)) static bool
workq_threadreq_admissible(struct workqueue *wq, struct uthread *uth,
		workq_threadreq_t req)
{
	if (req->tr_qos == WORKQ_THREAD_QOS_MANAGER) {
		return workq_may_start_event_mgr_thread(wq, uth);
	}
	if ((req->tr_flags & TR_FLAG_OVERCOMMIT) == 0) {
		return workq_constrained_allowance(wq, req->tr_qos, uth, true);
	}
	return true;
}