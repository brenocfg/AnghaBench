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
struct sk_buff {scalar_t__ len; void* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; } ;
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  dev; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct fec_enet_private {size_t skb_cur; int tx_full; int /*<<< orphan*/  hw_lock; struct bufdesc* cur_tx; struct bufdesc* dirty_tx; struct bufdesc* tx_bd_base; scalar_t__ hwp; struct sk_buff** tx_skbuff; void** tx_bounce; int /*<<< orphan*/  link; } ;
struct bufdesc {unsigned short cbd_sc; int /*<<< orphan*/  cbd_bufaddr; scalar_t__ cbd_datlen; } ;

/* Variables and functions */
 unsigned short BD_ENET_TX_INTR ; 
 unsigned short BD_ENET_TX_LAST ; 
 unsigned short BD_ENET_TX_READY ; 
 unsigned short BD_ENET_TX_STATS ; 
 unsigned short BD_ENET_TX_TC ; 
 unsigned short BD_ENET_TX_WRAP ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned long FEC_ALIGNMENT ; 
 int /*<<< orphan*/  FEC_ENET_TX_FRSIZE ; 
 scalar_t__ FEC_X_DES_ACTIVE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int TX_RING_MOD_MASK ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
fec_enet_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	struct bufdesc *bdp;
	void *bufaddr;
	unsigned short	status;
	unsigned long flags;

	if (!fep->link) {
		/* Link is down or autonegotiation is in progress. */
		return NETDEV_TX_BUSY;
	}

	spin_lock_irqsave(&fep->hw_lock, flags);
	/* Fill in a Tx ring entry */
	bdp = fep->cur_tx;

	status = bdp->cbd_sc;

	if (status & BD_ENET_TX_READY) {
		/* Ooops.  All transmit buffers are full.  Bail out.
		 * This should not happen, since dev->tbusy should be set.
		 */
		printk("%s: tx queue full!.\n", dev->name);
		spin_unlock_irqrestore(&fep->hw_lock, flags);
		return NETDEV_TX_BUSY;
	}

	/* Clear all of the status flags */
	status &= ~BD_ENET_TX_STATS;

	/* Set buffer length and buffer pointer */
	bufaddr = skb->data;
	bdp->cbd_datlen = skb->len;

	/*
	 * On some FEC implementations data must be aligned on
	 * 4-byte boundaries. Use bounce buffers to copy data
	 * and get it aligned. Ugh.
	 */
	if (((unsigned long) bufaddr) & FEC_ALIGNMENT) {
		unsigned int index;
		index = bdp - fep->tx_bd_base;
		memcpy(fep->tx_bounce[index], (void *)skb->data, skb->len);
		bufaddr = fep->tx_bounce[index];
	}

	/* Save skb pointer */
	fep->tx_skbuff[fep->skb_cur] = skb;

	dev->stats.tx_bytes += skb->len;
	fep->skb_cur = (fep->skb_cur+1) & TX_RING_MOD_MASK;

	/* Push the data cache so the CPM does not get stale memory
	 * data.
	 */
	bdp->cbd_bufaddr = dma_map_single(&dev->dev, bufaddr,
			FEC_ENET_TX_FRSIZE, DMA_TO_DEVICE);

	/* Send it on its way.  Tell FEC it's ready, interrupt when done,
	 * it's the last BD of the frame, and to put the CRC on the end.
	 */
	status |= (BD_ENET_TX_READY | BD_ENET_TX_INTR
			| BD_ENET_TX_LAST | BD_ENET_TX_TC);
	bdp->cbd_sc = status;

	dev->trans_start = jiffies;

	/* Trigger transmission start */
	writel(0, fep->hwp + FEC_X_DES_ACTIVE);

	/* If this was the last BD in the ring, start at the beginning again. */
	if (status & BD_ENET_TX_WRAP)
		bdp = fep->tx_bd_base;
	else
		bdp++;

	if (bdp == fep->dirty_tx) {
		fep->tx_full = 1;
		netif_stop_queue(dev);
	}

	fep->cur_tx = bdp;

	spin_unlock_irqrestore(&fep->hw_lock, flags);

	return NETDEV_TX_OK;
}