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
struct sk_buff {scalar_t__ len; } ;
struct sa1100_irda {int /*<<< orphan*/  txbuf_dma; int /*<<< orphan*/  dev; scalar_t__ newspeed; struct sk_buff* txskb; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int HSSR0_TUR ; 
 int HSSR1_TBY ; 
 int Ser2HSSR0 ; 
 int Ser2HSSR1 ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  sa1100_irda_rx_dma_start (struct sa1100_irda*) ; 
 int /*<<< orphan*/  sa1100_irda_set_speed (struct sa1100_irda*,scalar_t__) ; 

__attribute__((used)) static void sa1100_irda_txdma_irq(void *id)
{
	struct net_device *dev = id;
	struct sa1100_irda *si = netdev_priv(dev);
	struct sk_buff *skb = si->txskb;

	si->txskb = NULL;

	/*
	 * Wait for the transmission to complete.  Unfortunately,
	 * the hardware doesn't give us an interrupt to indicate
	 * "end of frame".
	 */
	do
		rmb();
	while (!(Ser2HSSR0 & HSSR0_TUR) || Ser2HSSR1 & HSSR1_TBY);

	/*
	 * Clear the transmit underrun bit.
	 */
	Ser2HSSR0 = HSSR0_TUR;

	/*
	 * Do we need to change speed?  Note that we're lazy
	 * here - we don't free the old rxskb.  We don't need
	 * to allocate a buffer either.
	 */
	if (si->newspeed) {
		sa1100_irda_set_speed(si, si->newspeed);
		si->newspeed = 0;
	}

	/*
	 * Start reception.  This disables the transmitter for
	 * us.  This will be using the existing RX buffer.
	 */
	sa1100_irda_rx_dma_start(si);

	/*
	 * Account and free the packet.
	 */
	if (skb) {
		dma_unmap_single(si->dev, si->txbuf_dma, skb->len, DMA_TO_DEVICE);
		dev->stats.tx_packets ++;
		dev->stats.tx_bytes += skb->len;
		dev_kfree_skb_irq(skb);
	}

	/*
	 * Make sure that the TX queue is available for sending
	 * (for retries).  TX has priority over RX at all times.
	 */
	netif_wake_queue(dev);
}