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
struct tx_queue {int tx_ring_size; int tx_desc_count; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_dropped; } ;
struct sk_buff {scalar_t__ len; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  dev; } ;
struct mv643xx_eth_private {struct tx_queue* txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_SKB_FRAGS ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ has_tiny_unaligned_frags (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  txq_submit_skb (struct tx_queue*,struct sk_buff*) ; 

__attribute__((used)) static int mv643xx_eth_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	int queue;
	struct tx_queue *txq;
	struct netdev_queue *nq;

	queue = skb_get_queue_mapping(skb);
	txq = mp->txq + queue;
	nq = netdev_get_tx_queue(dev, queue);

	if (has_tiny_unaligned_frags(skb) && __skb_linearize(skb)) {
		txq->tx_dropped++;
		dev_printk(KERN_DEBUG, &dev->dev,
			   "failed to linearize skb with tiny "
			   "unaligned fragment\n");
		return NETDEV_TX_BUSY;
	}

	if (txq->tx_ring_size - txq->tx_desc_count < MAX_SKB_FRAGS + 1) {
		if (net_ratelimit())
			dev_printk(KERN_ERR, &dev->dev, "tx queue full?!\n");
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	if (!txq_submit_skb(txq, skb)) {
		int entries_left;

		txq->tx_bytes += skb->len;
		txq->tx_packets++;
		dev->trans_start = jiffies;

		entries_left = txq->tx_ring_size - txq->tx_desc_count;
		if (entries_left < MAX_SKB_FRAGS + 1)
			netif_tx_stop_queue(nq);
	}

	return NETDEV_TX_OK;
}