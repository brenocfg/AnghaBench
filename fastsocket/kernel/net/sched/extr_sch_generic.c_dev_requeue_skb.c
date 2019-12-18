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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_3__ {int /*<<< orphan*/  requeues; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; struct sk_buff* gso_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 

__attribute__((used)) static inline int dev_requeue_skb(struct sk_buff *skb, struct Qdisc *q)
{
	q->gso_skb = skb;
	q->qstats.requeues++;
	q->q.qlen++;	/* it's still part of the queue */
	__netif_schedule(q);

	return 0;
}