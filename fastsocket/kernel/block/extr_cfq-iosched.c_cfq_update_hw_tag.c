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
struct cfq_queue {scalar_t__ dispatched; scalar_t__* queued; } ;
struct cfq_data {scalar_t__ rq_in_driver; scalar_t__ hw_tag_est_depth; int hw_tag; scalar_t__ rq_queued; int /*<<< orphan*/  hw_tag_samples; struct cfq_queue* active_queue; } ;

/* Variables and functions */
 scalar_t__ CFQ_HW_QUEUE_MIN ; 
 scalar_t__ cfq_cfqq_idle_window (struct cfq_queue*) ; 

__attribute__((used)) static void cfq_update_hw_tag(struct cfq_data *cfqd)
{
	struct cfq_queue *cfqq = cfqd->active_queue;

	if (cfqd->rq_in_driver > cfqd->hw_tag_est_depth)
		cfqd->hw_tag_est_depth = cfqd->rq_in_driver;

	if (cfqd->hw_tag == 1)
		return;

	if (cfqd->rq_queued <= CFQ_HW_QUEUE_MIN &&
	    cfqd->rq_in_driver <= CFQ_HW_QUEUE_MIN)
		return;

	/*
	 * If active queue hasn't enough requests and can idle, cfq might not
	 * dispatch sufficient requests to hardware. Don't zero hw_tag in this
	 * case
	 */
	if (cfqq && cfq_cfqq_idle_window(cfqq) &&
	    cfqq->dispatched + cfqq->queued[0] + cfqq->queued[1] <
	    CFQ_HW_QUEUE_MIN && cfqd->rq_in_driver < CFQ_HW_QUEUE_MIN)
		return;

	if (cfqd->hw_tag_samples++ < 50)
		return;

	if (cfqd->hw_tag_est_depth >= CFQ_HW_QUEUE_MIN)
		cfqd->hw_tag = 1;
	else
		cfqd->hw_tag = 0;
}