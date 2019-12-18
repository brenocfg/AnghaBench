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
struct net_device {int base_addr; scalar_t__ if_port; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct corkscrew_private {int /*<<< orphan*/ ** tx_skbuff; scalar_t__ full_bus_master_tx; int /*<<< orphan*/ ** rx_skbuff; scalar_t__ full_bus_master_rx; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ DownListPtr ; 
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 int RX_RING_SIZE ; 
 int RxDisable ; 
 int SetIntrEnb ; 
 int StatsDisable ; 
 int StopCoax ; 
 int TX_RING_SIZE ; 
 int TxDisable ; 
 scalar_t__ TxStatus ; 
 scalar_t__ UpListPtr ; 
 scalar_t__ XCVR_10base2 ; 
 int corkscrew_debug ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  queued_packet ; 
 int /*<<< orphan*/  rx_copy ; 
 int /*<<< orphan*/  rx_nocopy ; 
 int /*<<< orphan*/  update_stats (int,struct net_device*) ; 

__attribute__((used)) static int corkscrew_close(struct net_device *dev)
{
	struct corkscrew_private *vp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	int i;

	netif_stop_queue(dev);

	if (corkscrew_debug > 1) {
		pr_debug("%s: corkscrew_close() status %4.4x, Tx status %2.2x.\n",
		     dev->name, inw(ioaddr + EL3_STATUS),
		     inb(ioaddr + TxStatus));
		pr_debug("%s: corkscrew close stats: rx_nocopy %d rx_copy %d tx_queued %d.\n",
			dev->name, rx_nocopy, rx_copy, queued_packet);
	}

	del_timer(&vp->timer);

	/* Turn off statistics ASAP.  We update lp->stats below. */
	outw(StatsDisable, ioaddr + EL3_CMD);

	/* Disable the receiver and transmitter. */
	outw(RxDisable, ioaddr + EL3_CMD);
	outw(TxDisable, ioaddr + EL3_CMD);

	if (dev->if_port == XCVR_10base2)
		/* Turn off thinnet power.  Green! */
		outw(StopCoax, ioaddr + EL3_CMD);

	free_irq(dev->irq, dev);

	outw(SetIntrEnb | 0x0000, ioaddr + EL3_CMD);

	update_stats(ioaddr, dev);
	if (vp->full_bus_master_rx) {	/* Free Boomerang bus master Rx buffers. */
		outl(0, ioaddr + UpListPtr);
		for (i = 0; i < RX_RING_SIZE; i++)
			if (vp->rx_skbuff[i]) {
				dev_kfree_skb(vp->rx_skbuff[i]);
				vp->rx_skbuff[i] = NULL;
			}
	}
	if (vp->full_bus_master_tx) {	/* Free Boomerang bus master Tx buffers. */
		outl(0, ioaddr + DownListPtr);
		for (i = 0; i < TX_RING_SIZE; i++)
			if (vp->tx_skbuff[i]) {
				dev_kfree_skb(vp->tx_skbuff[i]);
				vp->tx_skbuff[i] = NULL;
			}
	}

	return 0;
}