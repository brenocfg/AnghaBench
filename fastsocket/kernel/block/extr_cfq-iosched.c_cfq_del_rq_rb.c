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
struct request {int dummy; } ;
struct cfq_queue {int /*<<< orphan*/ * p_root; int /*<<< orphan*/  p_node; int /*<<< orphan*/  sort_list; int /*<<< orphan*/ * queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 scalar_t__ cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_del_rq_rb(struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);
	const int sync = rq_is_sync(rq);

	BUG_ON(!cfqq->queued[sync]);
	cfqq->queued[sync]--;

	elv_rb_del(&cfqq->sort_list, rq);

	if (cfq_cfqq_on_rr(cfqq) && RB_EMPTY_ROOT(&cfqq->sort_list)) {
		/*
		 * Queue will be deleted from service tree when we actually
		 * expire it later. Right now just remove it from prio tree
		 * as it is empty.
		 */
		if (cfqq->p_root) {
			rb_erase(&cfqq->p_node, cfqq->p_root);
			cfqq->p_root = NULL;
		}
	}
}