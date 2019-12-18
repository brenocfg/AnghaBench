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
struct multiq_sched_data {int bands; int curband; struct Qdisc** queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; struct sk_buff* (* dequeue ) (struct Qdisc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_subqueue_stopped (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *multiq_dequeue(struct Qdisc *sch)
{
	struct multiq_sched_data *q = qdisc_priv(sch);
	struct Qdisc *qdisc;
	struct sk_buff *skb;
	int band;

	for (band = 0; band < q->bands; band++) {
		/* cycle through bands to ensure fairness */
		q->curband++;
		if (q->curband >= q->bands)
			q->curband = 0;

		/* Check that target subqueue is available before
		 * pulling an skb to avoid head-of-line blocking.
		 */
		if (!__netif_subqueue_stopped(qdisc_dev(sch), q->curband)) {
			qdisc = q->queues[q->curband];
			skb = qdisc->dequeue(qdisc);
			if (skb) {
				sch->q.qlen--;
				return skb;
			}
		}
	}
	return NULL;

}