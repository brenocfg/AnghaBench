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
struct sk_buff {int dummy; } ;
struct prio_sched_data {int bands; struct Qdisc** queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; struct sk_buff* (* dequeue ) (struct Qdisc*) ;} ;

/* Variables and functions */
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *prio_dequeue(struct Qdisc* sch)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	int prio;

	for (prio = 0; prio < q->bands; prio++) {
		struct Qdisc *qdisc = q->queues[prio];
		struct sk_buff *skb = qdisc->dequeue(qdisc);
		if (skb) {
			sch->q.qlen--;
			return skb;
		}
	}
	return NULL;

}