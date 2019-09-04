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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ thread_qos_t ;
struct workqueue {scalar_t__ wq_constrained_threads_scheduled; } ;
struct TYPE_2__ {scalar_t__ qos_bucket; } ;
struct uthread {int uu_workq_flags; TYPE_1__ uu_workq_pri; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int TRACE_wq_constrained_admission ; 
 int UT_WORKQ_OVERCOMMIT ; 
 scalar_t__ WORKQ_THREAD_QOS_MANAGER ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t _wq_bucket (scalar_t__) ; 
 int /*<<< orphan*/  _wq_thactive (struct workqueue*) ; 
 scalar_t__ _wq_thactive_aggregate_downto_qos (struct workqueue*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  workq_schedule_delayed_thread_creation (struct workqueue*,int /*<<< orphan*/ ) ; 
 scalar_t__ wq_max_constrained_threads ; 
 scalar_t__* wq_max_parallelism ; 

__attribute__((used)) static uint32_t
workq_constrained_allowance(struct workqueue *wq, thread_qos_t at_qos,
		struct uthread *uth, bool may_start_timer)
{
	assert(at_qos != WORKQ_THREAD_QOS_MANAGER);
	uint32_t count = 0;

	uint32_t max_count = wq->wq_constrained_threads_scheduled;
	if (uth && (uth->uu_workq_flags & UT_WORKQ_OVERCOMMIT) == 0) {
		/*
		 * don't count the current thread as scheduled
		 */
		assert(max_count > 0);
		max_count--;
	}
	if (max_count >= wq_max_constrained_threads) {
		WQ_TRACE_WQ(TRACE_wq_constrained_admission | DBG_FUNC_NONE, wq, 1,
				wq->wq_constrained_threads_scheduled,
				wq_max_constrained_threads, 0);
		/*
		 * we need 1 or more constrained threads to return to the kernel before
		 * we can dispatch additional work
		 */
		return 0;
	}
	max_count -= wq_max_constrained_threads;

	/*
	 * Compute a metric for many how many threads are active.  We find the
	 * highest priority request outstanding and then add up the number of
	 * active threads in that and all higher-priority buckets.  We'll also add
	 * any "busy" threads which are not active but blocked recently enough that
	 * we can't be sure they've gone idle yet.  We'll then compare this metric
	 * to our max concurrency to decide whether to add a new thread.
	 */

	uint32_t busycount, thactive_count;

	thactive_count = _wq_thactive_aggregate_downto_qos(wq, _wq_thactive(wq),
			at_qos, &busycount, NULL);

	if (uth && uth->uu_workq_pri.qos_bucket != WORKQ_THREAD_QOS_MANAGER &&
			at_qos <= uth->uu_workq_pri.qos_bucket) {
		/*
		 * Don't count this thread as currently active, but only if it's not
		 * a manager thread, as _wq_thactive_aggregate_downto_qos ignores active
		 * managers.
		 */
		assert(thactive_count > 0);
		thactive_count--;
	}

	count = wq_max_parallelism[_wq_bucket(at_qos)];
	if (count > thactive_count + busycount) {
		count -= thactive_count + busycount;
		WQ_TRACE_WQ(TRACE_wq_constrained_admission | DBG_FUNC_NONE, wq, 2,
				thactive_count, busycount, 0);
		return MIN(count, max_count);
	} else {
		WQ_TRACE_WQ(TRACE_wq_constrained_admission | DBG_FUNC_NONE, wq, 3,
				thactive_count, busycount, 0);
	}

	if (busycount && may_start_timer) {
		/*
		 * If this is called from the add timer, we won't have another timer
		 * fire when the thread exits the "busy" state, so rearm the timer.
		 */
		workq_schedule_delayed_thread_creation(wq, 0);
	}

	return 0;
}