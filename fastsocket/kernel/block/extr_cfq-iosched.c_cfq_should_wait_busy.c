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
struct cfq_queue {int slice_end; TYPE_1__* cfqg; } ;
struct cfq_io_context {int ttime_mean; int /*<<< orphan*/  ttime_samples; } ;
struct cfq_data {struct cfq_io_context* active_cic; } ;
struct TYPE_2__ {int nr_cfqq; } ;

/* Variables and functions */
 scalar_t__ cfq_slice_used (struct cfq_queue*) ; 
 int jiffies ; 
 scalar_t__ sample_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cfq_should_wait_busy(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	struct cfq_io_context *cic = cfqd->active_cic;

	/* If there are other queues in the group, don't wait */
	if (cfqq->cfqg->nr_cfqq > 1)
		return false;

	if (cfq_slice_used(cfqq))
		return true;

	/* if slice left is less than think time, wait busy */
	if (cic && sample_valid(cic->ttime_samples)
	    && (cfqq->slice_end - jiffies < cic->ttime_mean))
		return true;

	/*
	 * If think times is less than a jiffy than ttime_mean=0 and above
	 * will not be true. It might happen that slice has not expired yet
	 * but will expire soon (4-5 ns) during select_queue(). To cover the
	 * case where think time is less than a jiffy, mark the queue wait
	 * busy if only 1 jiffy is left in the slice.
	 */
	if (cfqq->slice_end - jiffies == 1)
		return true;

	return false;
}