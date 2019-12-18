#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct ep93xx_priv {int tx_pointer; int tx_pending; int /*<<< orphan*/  tx_pending_lock; TYPE_3__* descs; int /*<<< orphan*/ * tx_buf; TYPE_1__ stats; } ;
struct TYPE_6__ {TYPE_2__* tdesc; } ;
struct TYPE_5__ {int tdesc1; int /*<<< orphan*/  buf_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MAX_PKT_SIZE ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  REG_TXDENQ ; 
 int TDESC1_EOF ; 
 int TX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_and_csum_dev (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wrl (struct ep93xx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ep93xx_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ep93xx_priv *ep = netdev_priv(dev);
	int entry;

	if (unlikely(skb->len > MAX_PKT_SIZE)) {
		ep->stats.tx_dropped++;
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	entry = ep->tx_pointer;
	ep->tx_pointer = (ep->tx_pointer + 1) & (TX_QUEUE_ENTRIES - 1);

	ep->descs->tdesc[entry].tdesc1 =
		TDESC1_EOF | (entry << 16) | (skb->len & 0xfff);
	skb_copy_and_csum_dev(skb, ep->tx_buf[entry]);
	dma_sync_single_for_cpu(NULL, ep->descs->tdesc[entry].buf_addr,
				skb->len, DMA_TO_DEVICE);
	dev_kfree_skb(skb);

	dev->trans_start = jiffies;

	spin_lock_irq(&ep->tx_pending_lock);
	ep->tx_pending++;
	if (ep->tx_pending == TX_QUEUE_ENTRIES)
		netif_stop_queue(dev);
	spin_unlock_irq(&ep->tx_pending_lock);

	wrl(ep, REG_TXDENQ, 1);

	return NETDEV_TX_OK;
}