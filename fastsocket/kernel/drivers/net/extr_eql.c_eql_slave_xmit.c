#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int priority; scalar_t__ len; struct net_device* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  bytes_queued; struct net_device* dev; } ;
typedef  TYPE_2__ slave_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {TYPE_6__ queue; } ;
typedef  TYPE_3__ equalizer_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 TYPE_2__* __eql_schedule_slaves (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t eql_slave_xmit(struct sk_buff *skb, struct net_device *dev)
{
	equalizer_t *eql = netdev_priv(dev);
	slave_t *slave;

	spin_lock(&eql->queue.lock);

	slave = __eql_schedule_slaves(&eql->queue);
	if (slave) {
		struct net_device *slave_dev = slave->dev;

		skb->dev = slave_dev;
		skb->priority = 1;
		slave->bytes_queued += skb->len;
		dev_queue_xmit(skb);
		dev->stats.tx_packets++;
	} else {
		dev->stats.tx_dropped++;
		dev_kfree_skb(skb);
	}

	spin_unlock(&eql->queue.lock);

	return NETDEV_TX_OK;
}