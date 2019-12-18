#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ qlen; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {unsigned long expires; } ;
struct neigh_table {TYPE_3__ proxy_queue; TYPE_1__ proxy_timer; } ;
struct neigh_parms {unsigned long proxy_delay; scalar_t__ proxy_qlen; } ;
struct TYPE_7__ {unsigned long sched_next; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCALLY_ENQUEUED ; 
 TYPE_4__* NEIGH_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_3__*,struct sk_buff*) ; 
 scalar_t__ del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 unsigned long net_random () ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

void pneigh_enqueue(struct neigh_table *tbl, struct neigh_parms *p,
		    struct sk_buff *skb)
{
	unsigned long now = jiffies;
	unsigned long sched_next = now + (net_random() % p->proxy_delay);

	if (tbl->proxy_queue.qlen > p->proxy_qlen) {
		kfree_skb(skb);
		return;
	}

	NEIGH_CB(skb)->sched_next = sched_next;
	NEIGH_CB(skb)->flags |= LOCALLY_ENQUEUED;

	spin_lock(&tbl->proxy_queue.lock);
	if (del_timer(&tbl->proxy_timer)) {
		if (time_before(tbl->proxy_timer.expires, sched_next))
			sched_next = tbl->proxy_timer.expires;
	}
	skb_dst_drop(skb);
	dev_hold(skb->dev);
	__skb_queue_tail(&tbl->proxy_queue, skb);
	mod_timer(&tbl->proxy_timer, sched_next);
	spin_unlock(&tbl->proxy_queue.lock);
}