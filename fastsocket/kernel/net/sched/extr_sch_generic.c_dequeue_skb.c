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
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {struct sk_buff* (* dequeue ) (struct Qdisc*) ;TYPE_1__ q; struct sk_buff* gso_skb; } ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_queue_frozen (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 
 scalar_t__ unlikely (struct sk_buff*) ; 

__attribute__((used)) static inline struct sk_buff *dequeue_skb(struct Qdisc *q)
{
	struct sk_buff *skb = q->gso_skb;

	if (unlikely(skb)) {
		struct net_device *dev = qdisc_dev(q);
		struct netdev_queue *txq;

		/* check the reason of requeuing without tx lock first */
		txq = netdev_get_tx_queue(dev, skb_get_queue_mapping(skb));
		if (!netif_tx_queue_stopped(txq) &&
		    !netif_tx_queue_frozen(txq)) {
			q->gso_skb = NULL;
			q->q.qlen--;
		} else
			skb = NULL;
	} else {
		skb = q->dequeue(q);
	}

	return skb;
}