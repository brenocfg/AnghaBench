#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int wq_thactive_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ thread_qos_t ;
struct workqueue {int* wq_thscheduled_count; int /*<<< orphan*/ * wq_lastblocked_ts; } ;

/* Variables and functions */
 scalar_t__ THREAD_QOS_LAST ; 
 int WORKQ_NUM_QOS_BUCKETS ; 
 scalar_t__ WORKQ_THREAD_QOS_MAX ; 
 scalar_t__ WORKQ_THREAD_QOS_MIN ; 
 int WQ_THACTIVE_BUCKET_MASK ; 
 int WQ_THACTIVE_BUCKET_WIDTH ; 
 int _wq_bucket (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ workq_thread_is_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t
_wq_thactive_aggregate_downto_qos(struct workqueue *wq, wq_thactive_t v,
		thread_qos_t qos, uint32_t *busycount, uint32_t *max_busycount)
{
	uint32_t count = 0, active;
	uint64_t curtime;

	assert(WORKQ_THREAD_QOS_MIN <= qos && qos <= WORKQ_THREAD_QOS_MAX);

	if (busycount) {
		curtime = mach_absolute_time();
		*busycount = 0;
	}
	if (max_busycount) {
		*max_busycount = THREAD_QOS_LAST - qos;
	}

	int i = _wq_bucket(qos);
	v >>= i * WQ_THACTIVE_BUCKET_WIDTH;
	for (; i < WORKQ_NUM_QOS_BUCKETS; i++, v >>= WQ_THACTIVE_BUCKET_WIDTH) {
		active = v & WQ_THACTIVE_BUCKET_MASK;
		count += active;

		if (busycount && wq->wq_thscheduled_count[i] > active) {
			if (workq_thread_is_busy(curtime, &wq->wq_lastblocked_ts[i])) {
				/*
				 * We only consider the last blocked thread for a given bucket
				 * as busy because we don't want to take the list lock in each
				 * sched callback. However this is an approximation that could
				 * contribute to thread creation storms.
				 */
				(*busycount)++;
			}
		}
	}

	return count;
}