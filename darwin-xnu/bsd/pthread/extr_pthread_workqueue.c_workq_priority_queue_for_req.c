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
struct priority_queue {int dummy; } ;
struct workqueue {struct priority_queue wq_constrained_queue; struct priority_queue wq_overcommit_queue; struct priority_queue wq_special_queue; } ;
struct TYPE_3__ {int tr_flags; } ;

/* Variables and functions */
 int TR_FLAG_OVERCOMMIT ; 
 int TR_FLAG_WL_OUTSIDE_QOS ; 

__attribute__((used)) static inline struct priority_queue *
workq_priority_queue_for_req(struct workqueue *wq, workq_threadreq_t req)
{
	if (req->tr_flags & TR_FLAG_WL_OUTSIDE_QOS) {
		return &wq->wq_special_queue;
	} else if (req->tr_flags & TR_FLAG_OVERCOMMIT) {
		return &wq->wq_overcommit_queue;
	} else {
		return &wq->wq_constrained_queue;
	}
}