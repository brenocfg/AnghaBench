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
struct sa1100_irda {int /*<<< orphan*/  rxdma; int /*<<< orphan*/  txdma; scalar_t__ open; int /*<<< orphan*/ * irlap; int /*<<< orphan*/ * rxskb; int /*<<< orphan*/  rxbuf_dma; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  HPSIR_MAX_RXLEN ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  irlap_close (int /*<<< orphan*/ *) ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  sa1100_free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1100_irda_shutdown (struct sa1100_irda*) ; 
 int /*<<< orphan*/  sa1100_set_power (struct sa1100_irda*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_irda_stop(struct net_device *dev)
{
	struct sa1100_irda *si = netdev_priv(dev);

	disable_irq(dev->irq);
	sa1100_irda_shutdown(si);

	/*
	 * If we have been doing DMA receive, make sure we
	 * tidy that up cleanly.
	 */
	if (si->rxskb) {
		dma_unmap_single(si->dev, si->rxbuf_dma, HPSIR_MAX_RXLEN,
				 DMA_FROM_DEVICE);
		dev_kfree_skb(si->rxskb);
		si->rxskb = NULL;
	}

	/* Stop IrLAP */
	if (si->irlap) {
		irlap_close(si->irlap);
		si->irlap = NULL;
	}

	netif_stop_queue(dev);
	si->open = 0;

	/*
	 * Free resources
	 */
	sa1100_free_dma(si->txdma);
	sa1100_free_dma(si->rxdma);
	free_irq(dev->irq, dev);

	sa1100_set_power(si, 0);

	return 0;
}