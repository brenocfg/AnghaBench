#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 struct sk_buff* dequeue_skb (struct Qdisc*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct Qdisc*) ; 
 int sch_direct_xmit (struct sk_buff*,struct Qdisc*,struct net_device*,struct netdev_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int qdisc_restart(struct Qdisc *q)
{
	struct netdev_queue *txq;
	struct net_device *dev;
	spinlock_t *root_lock;
	struct sk_buff *skb;

	/* Dequeue packet */
	skb = dequeue_skb(q);
	if (unlikely(!skb))
		return 0;

	root_lock = qdisc_lock(q);
	dev = qdisc_dev(q);
	txq = netdev_get_tx_queue(dev, skb_get_queue_mapping(skb));

	return sch_direct_xmit(skb, q, dev, txq, root_lock);
}