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
struct rb_node {int dummy; } ;
struct cfq_rb_root {scalar_t__ min_vdisktime; int /*<<< orphan*/  rb; } ;
struct cfq_group {scalar_t__ vdisktime; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  nr_cfqq; } ;
struct cfq_data {struct cfq_rb_root grp_service_tree; } ;

/* Variables and functions */
 scalar_t__ CFQ_IDLE_DELAY ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_group_service_tree_add (struct cfq_rb_root*,struct cfq_group*) ; 
 struct cfq_group* rb_entry_cfqg (struct rb_node*) ; 
 struct rb_node* rb_last (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfq_group_notify_queue_add(struct cfq_data *cfqd, struct cfq_group *cfqg)
{
	struct cfq_rb_root *st = &cfqd->grp_service_tree;
	struct cfq_group *__cfqg;
	struct rb_node *n;

	cfqg->nr_cfqq++;
	if (!RB_EMPTY_NODE(&cfqg->rb_node))
		return;

	/*
	 * Currently put the group at the end. Later implement something
	 * so that groups get lesser vtime based on their weights, so that
	 * if group does not loose all if it was not continously backlogged.
	 */
	n = rb_last(&st->rb);
	if (n) {
		__cfqg = rb_entry_cfqg(n);
		cfqg->vdisktime = __cfqg->vdisktime + CFQ_IDLE_DELAY;
	} else
		cfqg->vdisktime = st->min_vdisktime;
	cfq_group_service_tree_add(st, cfqg);
}