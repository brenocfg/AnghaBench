#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dropped_resize; } ;
struct emac_instance {int rx_skb_size; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  mal_rx_chan; int /*<<< orphan*/  mal; scalar_t__ rx_slot; TYPE_5__ commac; TYPE_4__* ndev; struct sk_buff** rx_skb; TYPE_3__* ofdev; TYPE_2__* rx_desc; TYPE_1__ estats; struct sk_buff* rx_sg_skb; } ;
struct TYPE_9__ {int mtu; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int ctrl; scalar_t__ data_ptr; scalar_t__ data_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ EMAC_RX_SKB_HEADROOM ; 
 int ENOMEM ; 
 int ETH_DATA_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAL_COMMAC_RX_STOPPED ; 
 int MAL_RX_CTRL_EMPTY ; 
 int MAL_RX_CTRL_FIRST ; 
 int MAL_RX_CTRL_WRAP ; 
 int NUM_RX_BUFF ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_full_tx_reset (struct emac_instance*) ; 
 int /*<<< orphan*/  emac_netif_start (struct emac_instance*) ; 
 int /*<<< orphan*/  emac_netif_stop (struct emac_instance*) ; 
 int /*<<< orphan*/  emac_rx_disable (struct emac_instance*) ; 
 int /*<<< orphan*/  emac_rx_enable (struct emac_instance*) ; 
 int /*<<< orphan*/  emac_rx_size (int) ; 
 int emac_rx_skb_size (int) ; 
 int emac_rx_sync_size (int) ; 
 int /*<<< orphan*/  mal_disable_rx_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mal_enable_rx_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mal_set_rcbs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int emac_resize_rx_ring(struct emac_instance *dev, int new_mtu)
{
	int rx_sync_size = emac_rx_sync_size(new_mtu);
	int rx_skb_size = emac_rx_skb_size(new_mtu);
	int i, ret = 0;

	mutex_lock(&dev->link_lock);
	emac_netif_stop(dev);
	emac_rx_disable(dev);
	mal_disable_rx_channel(dev->mal, dev->mal_rx_chan);

	if (dev->rx_sg_skb) {
		++dev->estats.rx_dropped_resize;
		dev_kfree_skb(dev->rx_sg_skb);
		dev->rx_sg_skb = NULL;
	}

	/* Make a first pass over RX ring and mark BDs ready, dropping
	 * non-processed packets on the way. We need this as a separate pass
	 * to simplify error recovery in the case of allocation failure later.
	 */
	for (i = 0; i < NUM_RX_BUFF; ++i) {
		if (dev->rx_desc[i].ctrl & MAL_RX_CTRL_FIRST)
			++dev->estats.rx_dropped_resize;

		dev->rx_desc[i].data_len = 0;
		dev->rx_desc[i].ctrl = MAL_RX_CTRL_EMPTY |
		    (i == (NUM_RX_BUFF - 1) ? MAL_RX_CTRL_WRAP : 0);
	}

	/* Reallocate RX ring only if bigger skb buffers are required */
	if (rx_skb_size <= dev->rx_skb_size)
		goto skip;

	/* Second pass, allocate new skbs */
	for (i = 0; i < NUM_RX_BUFF; ++i) {
		struct sk_buff *skb = alloc_skb(rx_skb_size, GFP_ATOMIC);
		if (!skb) {
			ret = -ENOMEM;
			goto oom;
		}

		BUG_ON(!dev->rx_skb[i]);
		dev_kfree_skb(dev->rx_skb[i]);

		skb_reserve(skb, EMAC_RX_SKB_HEADROOM + 2);
		dev->rx_desc[i].data_ptr =
		    dma_map_single(&dev->ofdev->dev, skb->data - 2, rx_sync_size,
				   DMA_FROM_DEVICE) + 2;
		dev->rx_skb[i] = skb;
	}
 skip:
	/* Check if we need to change "Jumbo" bit in MR1 */
	if ((new_mtu > ETH_DATA_LEN) ^ (dev->ndev->mtu > ETH_DATA_LEN)) {
		/* This is to prevent starting RX channel in emac_rx_enable() */
		set_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags);

		dev->ndev->mtu = new_mtu;
		emac_full_tx_reset(dev);
	}

	mal_set_rcbs(dev->mal, dev->mal_rx_chan, emac_rx_size(new_mtu));
 oom:
	/* Restart RX */
	clear_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags);
	dev->rx_slot = 0;
	mal_enable_rx_channel(dev->mal, dev->mal_rx_chan);
	emac_rx_enable(dev);
	emac_netif_start(dev);
	mutex_unlock(&dev->link_lock);

	return ret;
}