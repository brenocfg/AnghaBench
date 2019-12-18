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
struct tc_red_qopt {scalar_t__ limit; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  Wlog; int /*<<< orphan*/  qth_max; int /*<<< orphan*/  qth_min; int /*<<< orphan*/  flags; } ;
struct red_sched_data {scalar_t__ limit; int /*<<< orphan*/  parms; struct Qdisc* qdisc; int /*<<< orphan*/  flags; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct Qdisc*) ; 
 int PTR_ERR (struct Qdisc*) ; 
 int /*<<< orphan*/  TCA_RED_MAX ; 
 size_t TCA_RED_PARMS ; 
 size_t TCA_RED_STAB ; 
 int /*<<< orphan*/  bfifo_qdisc_ops ; 
 struct Qdisc* fifo_create_dflt (struct Qdisc*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct tc_red_qopt* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 struct red_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  red_end_of_idle_period (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  red_policy ; 
 int /*<<< orphan*/  red_set_parms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tc_red_qopt*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 scalar_t__ skb_queue_empty (TYPE_1__*) ; 

__attribute__((used)) static int red_change(struct Qdisc *sch, struct nlattr *opt)
{
	struct red_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_RED_MAX + 1];
	struct tc_red_qopt *ctl;
	struct Qdisc *child = NULL;
	int err;

	if (opt == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_RED_MAX, opt, red_policy);
	if (err < 0)
		return err;

	if (tb[TCA_RED_PARMS] == NULL ||
	    tb[TCA_RED_STAB] == NULL)
		return -EINVAL;

	ctl = nla_data(tb[TCA_RED_PARMS]);

	if (ctl->limit > 0) {
		child = fifo_create_dflt(sch, &bfifo_qdisc_ops, ctl->limit);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	sch_tree_lock(sch);
	q->flags = ctl->flags;
	q->limit = ctl->limit;
	if (child) {
		qdisc_tree_decrease_qlen(q->qdisc, q->qdisc->q.qlen);
		qdisc_destroy(q->qdisc);
		q->qdisc = child;
	}

	red_set_parms(&q->parms, ctl->qth_min, ctl->qth_max, ctl->Wlog,
				 ctl->Plog, ctl->Scell_log,
				 nla_data(tb[TCA_RED_STAB]));

	if (skb_queue_empty(&sch->q))
		red_end_of_idle_period(&q->parms);

	sch_tree_unlock(sch);
	return 0;
}