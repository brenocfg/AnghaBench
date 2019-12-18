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
struct cfq_queue {scalar_t__ slice_end; TYPE_2__* cfqg; scalar_t__ dispatched; int /*<<< orphan*/  sort_list; } ;
struct cfq_io_context {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; TYPE_1__* ioc; } ;
struct cfq_data {long cfq_group_idle; unsigned long cfq_slice_idle; int /*<<< orphan*/  idle_slice_timer; struct cfq_io_context* active_cic; scalar_t__ hw_tag; int /*<<< orphan*/  queue; struct cfq_queue* active_queue; } ;
struct TYPE_4__ {int nr_cfqq; int /*<<< orphan*/  blkg; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_queue_nonrot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_set_idle_time_stats (int /*<<< orphan*/ *) ; 
 int cfq_cfqq_slice_new (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_wait_request (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_should_idle (struct cfq_data*,struct cfq_queue*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sample_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_arm_slice_timer(struct cfq_data *cfqd)
{
	struct cfq_queue *cfqq = cfqd->active_queue;
	struct cfq_io_context *cic;
	unsigned long sl, group_idle = 0;

	/*
	 * SSD device without seek penalty, disable idling. But only do so
	 * for devices that support queuing, otherwise we still have a problem
	 * with sync vs async workloads.
	 */
	if (blk_queue_nonrot(cfqd->queue) && cfqd->hw_tag)
		return;

	WARN_ON(!RB_EMPTY_ROOT(&cfqq->sort_list));
	WARN_ON(cfq_cfqq_slice_new(cfqq));

	/*
	 * idle is disabled, either manually or by past process history
	 */
	if (!cfq_should_idle(cfqd, cfqq)) {
		/* no queue idling. Check for group idling */
		if (cfqd->cfq_group_idle)
			group_idle = cfqd->cfq_group_idle;
		else
			return;
	}

	/*
	 * still active requests from this queue, don't idle
	 */
	if (cfqq->dispatched)
		return;

	/*
	 * task has exited, don't wait
	 */
	cic = cfqd->active_cic;
	if (!cic || !atomic_read(&cic->ioc->nr_tasks))
		return;

	/*
	 * If our average think time is larger than the remaining time
	 * slice, then don't idle. This avoids overrunning the allotted
	 * time slice.
	 */
	if (sample_valid(cic->ttime_samples) &&
	    (cfqq->slice_end - jiffies < cic->ttime_mean)) {
		cfq_log_cfqq(cfqd, cfqq, "Not idling. think_time:%d",
				cic->ttime_mean);
		return;
	}

	/* There are other queues in the group, don't do group idle */
	if (group_idle && cfqq->cfqg->nr_cfqq > 1)
		return;

	cfq_mark_cfqq_wait_request(cfqq);

	if (group_idle)
		sl = cfqd->cfq_group_idle;
	else
		sl = cfqd->cfq_slice_idle;

	mod_timer(&cfqd->idle_slice_timer, jiffies + sl);
	cfq_blkiocg_update_set_idle_time_stats(&cfqq->cfqg->blkg);
	cfq_log_cfqq(cfqd, cfqq, "arm_idle: %lu group_idle: %d", sl,
			group_idle ? 1 : 0);
}