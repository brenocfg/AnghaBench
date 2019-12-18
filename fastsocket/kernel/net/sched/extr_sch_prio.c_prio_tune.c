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
struct tc_prio_qopt {int bands; int* priomap; } ;
struct prio_sched_data {int bands; struct Qdisc** queues; int /*<<< orphan*/  prio2band; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int TCQ_PRIO_BANDS ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int TC_PRIO_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct tc_prio_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int prio_tune(struct Qdisc *sch, struct nlattr *opt)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	struct tc_prio_qopt *qopt;
	int i;

	if (nla_len(opt) < sizeof(*qopt))
		return -EINVAL;
	qopt = nla_data(opt);

	if (qopt->bands > TCQ_PRIO_BANDS || qopt->bands < 2)
		return -EINVAL;

	for (i=0; i<=TC_PRIO_MAX; i++) {
		if (qopt->priomap[i] >= qopt->bands)
			return -EINVAL;
	}

	sch_tree_lock(sch);
	q->bands = qopt->bands;
	memcpy(q->prio2band, qopt->priomap, TC_PRIO_MAX+1);

	for (i=q->bands; i<TCQ_PRIO_BANDS; i++) {
		struct Qdisc *child = q->queues[i];
		q->queues[i] = &noop_qdisc;
		if (child != &noop_qdisc) {
			qdisc_tree_decrease_qlen(child, child->q.qlen);
			qdisc_destroy(child);
		}
	}
	sch_tree_unlock(sch);

	for (i=0; i<q->bands; i++) {
		if (q->queues[i] == &noop_qdisc) {
			struct Qdisc *child, *old;
			child = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
						  &pfifo_qdisc_ops,
						  TC_H_MAKE(sch->handle, i + 1));
			if (child) {
				sch_tree_lock(sch);
				old = q->queues[i];
				q->queues[i] = child;

				if (old != &noop_qdisc) {
					qdisc_tree_decrease_qlen(old,
								 old->q.qlen);
					qdisc_destroy(old);
				}
				sch_tree_unlock(sch);
			}
		}
	}
	return 0;
}