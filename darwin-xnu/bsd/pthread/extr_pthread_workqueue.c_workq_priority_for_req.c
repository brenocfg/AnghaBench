#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* workq_threadreq_t ;
struct TYPE_7__ {int trp_flags; int trp_pri; } ;
typedef  TYPE_2__ workq_threadreq_param_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;
struct TYPE_6__ {int tr_flags; int /*<<< orphan*/  tr_qos; } ;

/* Variables and functions */
 int TRP_PRIORITY ; 
 int TR_FLAG_WL_OUTSIDE_QOS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ kqueue_threadreq_workloop_param (TYPE_1__*) ; 
 int thread_workq_pri_for_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
workq_priority_for_req(workq_threadreq_t req)
{
	thread_qos_t qos = req->tr_qos;

	if (req->tr_flags & TR_FLAG_WL_OUTSIDE_QOS) {
		workq_threadreq_param_t trp = kqueue_threadreq_workloop_param(req);
		assert(trp.trp_flags & TRP_PRIORITY);
		return trp.trp_pri;
	}
	return thread_workq_pri_for_qos(qos);
}