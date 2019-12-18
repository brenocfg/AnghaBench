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
struct cfq_rb_root {int count; } ;
struct cfq_queue {struct cfq_rb_root* service_tree; } ;
struct cfq_data {scalar_t__ cfq_slice_idle; scalar_t__ hw_tag; int /*<<< orphan*/  queue; } ;
typedef  enum wl_prio_t { ____Placeholder_wl_prio_t } wl_prio_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IDLE_WORKLOAD ; 
 scalar_t__ blk_queue_nonrot (int /*<<< orphan*/ ) ; 
 scalar_t__ cfq_cfqq_idle_window (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*,int) ; 
 int cfqq_prio (struct cfq_queue*) ; 

__attribute__((used)) static bool cfq_should_idle(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	enum wl_prio_t prio = cfqq_prio(cfqq);
	struct cfq_rb_root *service_tree = cfqq->service_tree;

	BUG_ON(!service_tree);
	BUG_ON(!service_tree->count);

	/* We never do for idle class queues. */
	if (prio == IDLE_WORKLOAD)
		return false;

	/* Don't idle if slice idling is disabled by the user */
	if (cfqd->cfq_slice_idle == 0)
		return false;

	/* We do for queues that were marked with idle window flag. */
	if (cfq_cfqq_idle_window(cfqq) &&
	   !(blk_queue_nonrot(cfqd->queue) && cfqd->hw_tag))
		return true;

	/*
	 * Otherwise, we do only if they are the last ones
	 * in their service tree.
	 */
	if (service_tree->count == 1 && cfq_cfqq_sync(cfqq))
		return 1;
	cfq_log_cfqq(cfqd, cfqq, "Not idling. st->count:%d",
			service_tree->count);
	return 0;
}