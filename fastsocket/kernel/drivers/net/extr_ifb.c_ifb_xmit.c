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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  iif; scalar_t__ len; int /*<<< orphan*/  tc_verd; } ;
struct net_device_stats {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {scalar_t__ tx_queue_len; int /*<<< orphan*/  trans_start; struct net_device_stats stats; } ;
struct ifb_private {int tasklet_pending; int /*<<< orphan*/  ifb_tasklet; int /*<<< orphan*/  rq; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int AT_EGRESS ; 
 int AT_INGRESS ; 
 int G_TC_FROM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ifb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t ifb_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ifb_private *dp = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	u32 from = G_TC_FROM(skb->tc_verd);

	stats->rx_packets++;
	stats->rx_bytes+=skb->len;

	if (!(from & (AT_INGRESS|AT_EGRESS)) || !skb->iif) {
		dev_kfree_skb(skb);
		stats->rx_dropped++;
		return NETDEV_TX_OK;
	}

	if (skb_queue_len(&dp->rq) >= dev->tx_queue_len) {
		netif_stop_queue(dev);
	}

	dev->trans_start = jiffies;
	skb_queue_tail(&dp->rq, skb);
	if (!dp->tasklet_pending) {
		dp->tasklet_pending = 1;
		tasklet_schedule(&dp->ifb_tasklet);
	}

	return NETDEV_TX_OK;
}