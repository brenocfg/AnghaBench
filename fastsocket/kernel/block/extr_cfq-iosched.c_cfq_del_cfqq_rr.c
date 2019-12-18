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
struct cfq_queue {int /*<<< orphan*/  cfqg; int /*<<< orphan*/ * p_root; int /*<<< orphan*/  p_node; int /*<<< orphan*/ * service_tree; int /*<<< orphan*/  rb_node; } ;
struct cfq_data {int /*<<< orphan*/  busy_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_group_notify_queue_del (struct cfq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfq_del_cfqq_rr(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	cfq_log_cfqq(cfqd, cfqq, "del_from_rr");
	BUG_ON(!cfq_cfqq_on_rr(cfqq));
	cfq_clear_cfqq_on_rr(cfqq);

	if (!RB_EMPTY_NODE(&cfqq->rb_node)) {
		cfq_rb_erase(&cfqq->rb_node, cfqq->service_tree);
		cfqq->service_tree = NULL;
	}
	if (cfqq->p_root) {
		rb_erase(&cfqq->p_node, cfqq->p_root);
		cfqq->p_root = NULL;
	}

	cfq_group_notify_queue_del(cfqd, cfqq->cfqg);
	BUG_ON(!cfqd->busy_queues);
	cfqd->busy_queues--;
}