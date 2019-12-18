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
typedef  unsigned int u32 ;
struct txfcb {int dummy; } ;
struct txbd8 {unsigned int lstatus; unsigned int bufPtr; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_3__ stats; int /*<<< orphan*/  trans_start; } ;
struct gfar_private {unsigned int num_txbdfree; size_t skb_curtx; int /*<<< orphan*/  txlock; TYPE_4__* regs; int /*<<< orphan*/  tx_ring_size; struct txbd8* cur_tx; TYPE_2__* ofdev; struct sk_buff** tx_skbuff; scalar_t__ vlgrp; struct txbd8* tx_bd_base; } ;
struct TYPE_10__ {unsigned int nr_frags; TYPE_1__* frags; } ;
struct TYPE_9__ {int /*<<< orphan*/  tstat; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {unsigned int size; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 unsigned int BD_LFLAG (int) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ GMAC_FCB_LEN ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  TSTAT_CLEAR_THALT ; 
 int TXBD_CRC ; 
 int TXBD_INTERRUPT ; 
 int TXBD_LAST ; 
 int TXBD_READY ; 
 int TXBD_TOE ; 
 int TX_RING_MOD_MASK (int /*<<< orphan*/ ) ; 
 unsigned int dma_map_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eieio () ; 
 struct txfcb* gfar_add_fcb (struct sk_buff*) ; 
 int /*<<< orphan*/  gfar_tx_checksum (struct sk_buff*,struct txfcb*) ; 
 int /*<<< orphan*/  gfar_tx_vlan (struct sk_buff*,struct txfcb*) ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 void* next_txbd (struct txbd8*,struct txbd8*,int /*<<< orphan*/ ) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int gfar_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	struct txfcb *fcb = NULL;
	struct txbd8 *txbdp, *txbdp_start, *base;
	u32 lstatus;
	int i;
	u32 bufaddr;
	unsigned long flags;
	unsigned int nr_frags, length;

	base = priv->tx_bd_base;

	/* make space for additional header when fcb is needed */
	if (((skb->ip_summed == CHECKSUM_PARTIAL) ||
			(priv->vlgrp && vlan_tx_tag_present(skb))) &&
			(skb_headroom(skb) < GMAC_FCB_LEN)) {
		struct sk_buff *skb_new;

		skb_new = skb_realloc_headroom(skb, GMAC_FCB_LEN);
		if (!skb_new) {
			dev->stats.tx_errors++;
			kfree_skb(skb);
			return NETDEV_TX_OK;
		}
		kfree_skb(skb);
		skb = skb_new;
	}

	/* total number of fragments in the SKB */
	nr_frags = skb_shinfo(skb)->nr_frags;

	spin_lock_irqsave(&priv->txlock, flags);

	/* check if there is space to queue this packet */
	if ((nr_frags+1) > priv->num_txbdfree) {
		/* no space, stop the queue */
		netif_stop_queue(dev);
		dev->stats.tx_fifo_errors++;
		spin_unlock_irqrestore(&priv->txlock, flags);
		return NETDEV_TX_BUSY;
	}

	/* Update transmit stats */
	dev->stats.tx_bytes += skb->len;

	txbdp = txbdp_start = priv->cur_tx;

	if (nr_frags == 0) {
		lstatus = txbdp->lstatus | BD_LFLAG(TXBD_LAST | TXBD_INTERRUPT);
	} else {
		/* Place the fragment addresses and lengths into the TxBDs */
		for (i = 0; i < nr_frags; i++) {
			/* Point at the next BD, wrapping as needed */
			txbdp = next_txbd(txbdp, base, priv->tx_ring_size);

			length = skb_shinfo(skb)->frags[i].size;

			lstatus = txbdp->lstatus | length |
				BD_LFLAG(TXBD_READY);

			/* Handle the last BD specially */
			if (i == nr_frags - 1)
				lstatus |= BD_LFLAG(TXBD_LAST | TXBD_INTERRUPT);

			bufaddr = dma_map_page(&priv->ofdev->dev,
					skb_shinfo(skb)->frags[i].page,
					skb_shinfo(skb)->frags[i].page_offset,
					length,
					DMA_TO_DEVICE);

			/* set the TxBD length and buffer pointer */
			txbdp->bufPtr = bufaddr;
			txbdp->lstatus = lstatus;
		}

		lstatus = txbdp_start->lstatus;
	}

	/* Set up checksumming */
	if (CHECKSUM_PARTIAL == skb->ip_summed) {
		fcb = gfar_add_fcb(skb);
		lstatus |= BD_LFLAG(TXBD_TOE);
		gfar_tx_checksum(skb, fcb);
	}

	if (priv->vlgrp && vlan_tx_tag_present(skb)) {
		if (unlikely(NULL == fcb)) {
			fcb = gfar_add_fcb(skb);
			lstatus |= BD_LFLAG(TXBD_TOE);
		}

		gfar_tx_vlan(skb, fcb);
	}

	/* setup the TxBD length and buffer pointer for the first BD */
	priv->tx_skbuff[priv->skb_curtx] = skb;
	txbdp_start->bufPtr = dma_map_single(&priv->ofdev->dev, skb->data,
			skb_headlen(skb), DMA_TO_DEVICE);

	lstatus |= BD_LFLAG(TXBD_CRC | TXBD_READY) | skb_headlen(skb);

	/*
	 * The powerpc-specific eieio() is used, as wmb() has too strong
	 * semantics (it requires synchronization between cacheable and
	 * uncacheable mappings, which eieio doesn't provide and which we
	 * don't need), thus requiring a more expensive sync instruction.  At
	 * some point, the set of architecture-independent barrier functions
	 * should be expanded to include weaker barriers.
	 */
	eieio();

	txbdp_start->lstatus = lstatus;

	/* Update the current skb pointer to the next entry we will use
	 * (wrapping if necessary) */
	priv->skb_curtx = (priv->skb_curtx + 1) &
		TX_RING_MOD_MASK(priv->tx_ring_size);

	priv->cur_tx = next_txbd(txbdp, base, priv->tx_ring_size);

	/* reduce TxBD free count */
	priv->num_txbdfree -= (nr_frags + 1);

	dev->trans_start = jiffies;

	/* If the next BD still needs to be cleaned up, then the bds
	   are full.  We need to tell the kernel to stop sending us stuff. */
	if (!priv->num_txbdfree) {
		netif_stop_queue(dev);

		dev->stats.tx_fifo_errors++;
	}

	/* Tell the DMA to go go go */
	gfar_write(&priv->regs->tstat, TSTAT_CLEAR_THALT);

	/* Unlock priv */
	spin_unlock_irqrestore(&priv->txlock, flags);

	return NETDEV_TX_OK;
}