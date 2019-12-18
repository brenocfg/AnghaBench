#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct prio_sched_data {int bands; struct Qdisc** queues; } ;
struct TYPE_3__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; TYPE_2__* ops; } ;
struct TYPE_4__ {unsigned int (* drop ) (struct Qdisc*) ;} ;

/* Variables and functions */
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 unsigned int stub1 (struct Qdisc*) ; 

__attribute__((used)) static unsigned int prio_drop(struct Qdisc* sch)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	int prio;
	unsigned int len;
	struct Qdisc *qdisc;

	for (prio = q->bands-1; prio >= 0; prio--) {
		qdisc = q->queues[prio];
		if (qdisc->ops->drop && (len = qdisc->ops->drop(qdisc)) != 0) {
			sch->q.qlen--;
			return len;
		}
	}
	return 0;
}