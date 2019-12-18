#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct htb_sched {scalar_t__ wait_pq; int /*<<< orphan*/  clhash; } ;
struct TYPE_10__ {TYPE_6__* q; } ;
struct TYPE_11__ {TYPE_3__ leaf; } ;
struct htb_class {scalar_t__ cmode; scalar_t__ refcnt; scalar_t__ level; int /*<<< orphan*/  pq_node; scalar_t__ prio_activity; TYPE_5__* parent; int /*<<< orphan*/  common; TYPE_4__ un; scalar_t__ filter_cnt; scalar_t__ children; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;
struct TYPE_9__ {unsigned int qlen; } ;
struct TYPE_13__ {TYPE_2__ q; } ;
struct TYPE_8__ {int /*<<< orphan*/  classid; } ;
struct TYPE_12__ {int /*<<< orphan*/  children; TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 scalar_t__ HTB_CAN_SEND ; 
 int /*<<< orphan*/  htb_deactivate (struct htb_sched*,struct htb_class*) ; 
 scalar_t__ htb_parent_last_child (struct htb_class*) ; 
 int /*<<< orphan*/  htb_parent_to_leaf (struct htb_sched*,struct htb_class*,struct Qdisc*) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  qdisc_class_hash_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct htb_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (TYPE_6__*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (TYPE_6__*,unsigned int) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int htb_delete(struct Qdisc *sch, unsigned long arg)
{
	struct htb_sched *q = qdisc_priv(sch);
	struct htb_class *cl = (struct htb_class *)arg;
	unsigned int qlen;
	struct Qdisc *new_q = NULL;
	int last_child = 0;

	// TODO: why don't allow to delete subtree ? references ? does
	// tc subsys quarantee us that in htb_destroy it holds no class
	// refs so that we can remove children safely there ?
	if (cl->children || cl->filter_cnt)
		return -EBUSY;

	if (!cl->level && htb_parent_last_child(cl)) {
		new_q = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
					  &pfifo_qdisc_ops,
					  cl->parent->common.classid);
		last_child = 1;
	}

	sch_tree_lock(sch);

	if (!cl->level) {
		qlen = cl->un.leaf.q->q.qlen;
		qdisc_reset(cl->un.leaf.q);
		qdisc_tree_decrease_qlen(cl->un.leaf.q, qlen);
	}

	/* delete from hash and active; remainder in destroy_class */
	qdisc_class_hash_remove(&q->clhash, &cl->common);
	if (cl->parent)
		cl->parent->children--;

	if (cl->prio_activity)
		htb_deactivate(q, cl);

	if (cl->cmode != HTB_CAN_SEND)
		htb_safe_rb_erase(&cl->pq_node, q->wait_pq + cl->level);

	if (last_child)
		htb_parent_to_leaf(q, cl, new_q);

	BUG_ON(--cl->refcnt == 0);
	/*
	 * This shouldn't happen: we "hold" one cops->get() when called
	 * from tc_ctl_tclass; the destroy method is done from cops->put().
	 */

	sch_tree_unlock(sch);
	return 0;
}