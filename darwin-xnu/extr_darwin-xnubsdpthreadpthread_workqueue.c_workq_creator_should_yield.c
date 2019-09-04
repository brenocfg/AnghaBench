#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ thread_qos_t ;
struct workqueue {scalar_t__ wq_fulfilled; scalar_t__* wq_thscheduled_count; } ;
struct TYPE_3__ {scalar_t__ fulfilled_snapshot; } ;
struct TYPE_4__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {TYPE_2__ uu_save; int /*<<< orphan*/  uu_workq_pri; } ;

/* Variables and functions */
 scalar_t__ THREAD_QOS_USER_INTERACTIVE ; 
 int /*<<< orphan*/  TRACE_wq_creator_yield ; 
 int WORKQ_NUM_QOS_BUCKETS ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int /*<<< orphan*/ ,struct workqueue*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t _wq_bucket (scalar_t__) ; 
 scalar_t__ workq_pri_override (int /*<<< orphan*/ ) ; 
 scalar_t__* wq_max_parallelism ; 

__attribute__((used)) static bool
workq_creator_should_yield(struct workqueue *wq, struct uthread *uth)
{
	thread_qos_t qos = workq_pri_override(uth->uu_workq_pri);

	if (qos >= THREAD_QOS_USER_INTERACTIVE) {
		return false;
	}

	uint32_t snapshot = uth->uu_save.uus_workq_park_data.fulfilled_snapshot;
	if (wq->wq_fulfilled == snapshot) {
		return false;
	}

	uint32_t cnt = 0, conc = wq_max_parallelism[_wq_bucket(qos)];
	if (wq->wq_fulfilled - snapshot > conc) {
		/* we fulfilled more than NCPU requests since being dispatched */
		WQ_TRACE_WQ(TRACE_wq_creator_yield, wq, 1,
				wq->wq_fulfilled, snapshot, 0);
		return true;
	}

	for (int i = _wq_bucket(qos); i < WORKQ_NUM_QOS_BUCKETS; i++) {
		cnt += wq->wq_thscheduled_count[i];
	}
	if (conc <= cnt) {
		/* We fulfilled requests and have more than NCPU scheduled threads */
		WQ_TRACE_WQ(TRACE_wq_creator_yield, wq, 2,
				wq->wq_fulfilled, snapshot, 0);
		return true;
	}

	return false;
}