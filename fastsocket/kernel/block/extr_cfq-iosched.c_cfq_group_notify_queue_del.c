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
struct cfq_rb_root {int /*<<< orphan*/ * active; } ;
struct cfq_group {int nr_cfqq; int /*<<< orphan*/  blkg; scalar_t__ saved_workload_slice; int /*<<< orphan*/  rb_node; } ;
struct cfq_data {struct cfq_rb_root grp_service_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_dequeue_stats (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfq_group_service_tree_del (struct cfq_rb_root*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_log_cfqg (struct cfq_data*,struct cfq_group*,char*) ; 

__attribute__((used)) static void
cfq_group_notify_queue_del(struct cfq_data *cfqd, struct cfq_group *cfqg)
{
	struct cfq_rb_root *st = &cfqd->grp_service_tree;

	if (st->active == &cfqg->rb_node)
		st->active = NULL;

	BUG_ON(cfqg->nr_cfqq < 1);
	cfqg->nr_cfqq--;

	/* If there are other cfq queues under this group, don't delete it */
	if (cfqg->nr_cfqq)
		return;

	cfq_log_cfqg(cfqd, cfqg, "del_from_rr group");
	cfq_group_service_tree_del(st, cfqg);
	cfqg->saved_workload_slice = 0;
	cfq_blkiocg_update_dequeue_stats(&cfqg->blkg, 1);
}