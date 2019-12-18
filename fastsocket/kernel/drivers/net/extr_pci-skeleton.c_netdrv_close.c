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
struct netdrv_private {int /*<<< orphan*/ * tx_bufs; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  tx_bufs_dma; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; void* mmio_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_missed_errors; } ;
struct net_device {int /*<<< orphan*/  irq; TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cfg9346 ; 
 int Cfg9346_Lock ; 
 int Cfg9346_Unlock ; 
 int /*<<< orphan*/  ChipCmd ; 
 int ChipCmdClear ; 
 int /*<<< orphan*/  Config1 ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  NETDRV_R16 (int /*<<< orphan*/ ) ; 
 scalar_t__ NETDRV_R32 (int /*<<< orphan*/ ) ; 
 int NETDRV_R8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDRV_W16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NETDRV_W32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDRV_W8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RX_BUF_TOT_LEN ; 
 int /*<<< orphan*/  RxMissed ; 
 int /*<<< orphan*/  TX_BUF_TOT_LEN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct netdrv_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdrv_tx_clear (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int netdrv_close (struct net_device *dev)
{
	struct netdrv_private *tp = netdev_priv(dev);
	void *ioaddr = tp->mmio_addr;
	unsigned long flags;

	DPRINTK ("ENTER\n");

	netif_stop_queue (dev);

	DPRINTK ("%s: Shutting down ethercard, status was 0x%4.4x.\n",
			dev->name, NETDRV_R16 (IntrStatus));

	del_timer_sync (&tp->timer);

	spin_lock_irqsave (&tp->lock, flags);

	/* Stop the chip's Tx and Rx DMA processes. */
	NETDRV_W8 (ChipCmd, (NETDRV_R8 (ChipCmd) & ChipCmdClear));

	/* Disable interrupts by clearing the interrupt mask. */
	NETDRV_W16 (IntrMask, 0x0000);

	/* Update the error counts. */
	dev->stats.rx_missed_errors += NETDRV_R32 (RxMissed);
	NETDRV_W32 (RxMissed, 0);

	spin_unlock_irqrestore (&tp->lock, flags);

	free_irq (dev->irq, dev);

	netdrv_tx_clear (dev);

	pci_free_consistent(tp->pci_dev, RX_BUF_TOT_LEN,
			    tp->rx_ring, tp->rx_ring_dma);
	pci_free_consistent(tp->pci_dev, TX_BUF_TOT_LEN,
			    tp->tx_bufs, tp->tx_bufs_dma);
	tp->rx_ring = NULL;
	tp->tx_bufs = NULL;

	/* Green! Put the chip in low-power mode. */
	NETDRV_W8 (Cfg9346, Cfg9346_Unlock);
	NETDRV_W8 (Config1, 0x03);
	NETDRV_W8 (Cfg9346, Cfg9346_Lock);

	DPRINTK ("EXIT\n");
	return 0;
}