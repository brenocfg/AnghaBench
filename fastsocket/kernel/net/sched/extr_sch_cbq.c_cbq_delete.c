#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cbq_class {scalar_t__ refcnt; scalar_t__ defmap; int /*<<< orphan*/  tparent; scalar_t__ next_alive; TYPE_2__* q; scalar_t__ children; scalar_t__ filters; } ;
struct cbq_sched_data {struct cbq_class* rx_class; struct cbq_class* tx_borrowed; struct cbq_class* tx_class; struct cbq_class link; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {unsigned int qlen; } ;
struct TYPE_5__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  cbq_adjust_levels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbq_deactivate_class (struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_rmprio (struct cbq_sched_data*,struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_sync_defmap (struct cbq_class*) ; 
 int /*<<< orphan*/  cbq_unlink_class (struct cbq_class*) ; 
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int cbq_delete(struct Qdisc *sch, unsigned long arg)
{
	struct cbq_sched_data *q = qdisc_priv(sch);
	struct cbq_class *cl = (struct cbq_class*)arg;
	unsigned int qlen;

	if (cl->filters || cl->children || cl == &q->link)
		return -EBUSY;

	sch_tree_lock(sch);

	qlen = cl->q->q.qlen;
	qdisc_reset(cl->q);
	qdisc_tree_decrease_qlen(cl->q, qlen);

	if (cl->next_alive)
		cbq_deactivate_class(cl);

	if (q->tx_borrowed == cl)
		q->tx_borrowed = q->tx_class;
	if (q->tx_class == cl) {
		q->tx_class = NULL;
		q->tx_borrowed = NULL;
	}
#ifdef CONFIG_NET_CLS_ACT
	if (q->rx_class == cl)
		q->rx_class = NULL;
#endif

	cbq_unlink_class(cl);
	cbq_adjust_levels(cl->tparent);
	cl->defmap = 0;
	cbq_sync_defmap(cl);

	cbq_rmprio(q, cl);
	sch_tree_unlock(sch);

	BUG_ON(--cl->refcnt == 0);
	/*
	 * This shouldn't happen: we "hold" one cops->get() when called
	 * from tc_ctl_tclass; the destroy method is done from cops->put().
	 */

	return 0;
}