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
struct sk_buff {scalar_t__ len; struct net_device* dev; } ;
struct packet_task {struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct eth1394_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct packet_task*) ; 
 struct eth1394_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  packet_task_cache ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ether1394_dg_complete(struct packet_task *ptask, int fail)
{
	struct sk_buff *skb = ptask->skb;
	struct net_device *dev = skb->dev;
	struct eth1394_priv *priv = netdev_priv(dev);
	unsigned long flags;

	/* Statistics */
	spin_lock_irqsave(&priv->lock, flags);
	if (fail) {
		dev->stats.tx_dropped++;
		dev->stats.tx_errors++;
	} else {
		dev->stats.tx_bytes += skb->len;
		dev->stats.tx_packets++;
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_kfree_skb_any(skb);
	kmem_cache_free(packet_task_cache, ptask);
}