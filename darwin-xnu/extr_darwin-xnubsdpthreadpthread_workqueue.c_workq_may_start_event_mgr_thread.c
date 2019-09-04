#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct workqueue {scalar_t__* wq_thscheduled_count; } ;
struct TYPE_2__ {scalar_t__ qos_bucket; } ;
struct uthread {TYPE_1__ uu_workq_pri; } ;

/* Variables and functions */
 scalar_t__ WORKQ_THREAD_QOS_MANAGER ; 
 size_t _wq_bucket (scalar_t__) ; 

__attribute__((used)) static inline bool
workq_may_start_event_mgr_thread(struct workqueue *wq, struct uthread *uth)
{
	/*
	 * There's an event manager request and either:
	 * - no event manager currently running
	 * - we are re-using the event manager
	 */
	return wq->wq_thscheduled_count[_wq_bucket(WORKQ_THREAD_QOS_MANAGER)] == 0 ||
			(uth && uth->uu_workq_pri.qos_bucket == WORKQ_THREAD_QOS_MANAGER);
}