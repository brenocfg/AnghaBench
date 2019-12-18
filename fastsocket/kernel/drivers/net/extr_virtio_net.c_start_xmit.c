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
struct virtnet_info {int /*<<< orphan*/  svq; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ free_old_xmit_skbs (struct virtnet_info*) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_enable_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_enable_cb_delayed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 
 int xmit_skb (struct virtnet_info*,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);
	int capacity;

again:
	/* Free up any pending old buffers before queueing new ones. */
	free_old_xmit_skbs(vi);

	/* Try to transmit */
	capacity = xmit_skb(vi, skb);

	/* This can happen with OOM and indirect buffers. */
	if (unlikely(capacity < 0)) {
		netif_stop_queue(dev);
		dev_warn(&dev->dev, "Unexpected full queue\n");
		if (unlikely(!virtqueue_enable_cb(vi->svq))) {
			virtqueue_disable_cb(vi->svq);
			netif_start_queue(dev);
			goto again;
		}
		return NETDEV_TX_BUSY;
	}
	virtqueue_kick(vi->svq);

	/* Don't wait up for transmitted skbs to be freed. */
	skb_orphan(skb);
	nf_reset(skb);

	/* Apparently nice girls don't return TX_BUSY; stop the queue
	 * before it gets out of hand.  Naturally, this wastes entries. */
	if (capacity < 2+MAX_SKB_FRAGS) {
		netif_stop_queue(dev);
		if (unlikely(!virtqueue_enable_cb_delayed(vi->svq))) {
			/* More just got used, free them then recheck. */
			capacity += free_old_xmit_skbs(vi);
			if (capacity >= 2+MAX_SKB_FRAGS) {
				netif_start_queue(dev);
				virtqueue_disable_cb(vi->svq);
			}
		}
	}

	return NETDEV_TX_OK;
}