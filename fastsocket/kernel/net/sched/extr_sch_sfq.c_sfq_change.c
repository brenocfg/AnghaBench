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
struct tc_sfq_qopt {int perturb_period; scalar_t__ limit; scalar_t__ quantum; } ;
struct sfq_sched_data {int perturb_period; scalar_t__ limit; int /*<<< orphan*/  perturbation; int /*<<< orphan*/  perturb_timer; int /*<<< orphan*/  quantum; } ;
struct nlattr {scalar_t__ nla_len; } ;
struct TYPE_2__ {unsigned int qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 scalar_t__ SFQ_DEPTH ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  net_random () ; 
 scalar_t__ nla_attr_size (int) ; 
 struct tc_sfq_qopt* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (struct Qdisc*,unsigned int) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 int /*<<< orphan*/  sfq_drop (struct Qdisc*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int sfq_change(struct Qdisc *sch, struct nlattr *opt)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	struct tc_sfq_qopt *ctl = nla_data(opt);
	unsigned int qlen;

	if (opt->nla_len < nla_attr_size(sizeof(*ctl)))
		return -EINVAL;

	sch_tree_lock(sch);
	q->quantum = ctl->quantum ? : psched_mtu(qdisc_dev(sch));
	q->perturb_period = ctl->perturb_period * HZ;
	if (ctl->limit)
		q->limit = min_t(u32, ctl->limit, SFQ_DEPTH - 1);

	qlen = sch->q.qlen;
	while (sch->q.qlen > q->limit)
		sfq_drop(sch);
	qdisc_tree_decrease_qlen(sch, qlen - sch->q.qlen);

	del_timer(&q->perturb_timer);
	if (q->perturb_period) {
		mod_timer(&q->perturb_timer, jiffies + q->perturb_period);
		q->perturbation = net_random();
	}
	sch_tree_unlock(sch);
	return 0;
}