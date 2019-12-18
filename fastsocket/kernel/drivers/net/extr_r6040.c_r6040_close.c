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
struct r6040_private {int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  timer; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DESC_SIZE ; 
 int /*<<< orphan*/  TX_DESC_SIZE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r6040_down (struct net_device*) ; 
 int /*<<< orphan*/  r6040_free_rxbufs (struct net_device*) ; 
 int /*<<< orphan*/  r6040_free_txbufs (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r6040_close(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	struct pci_dev *pdev = lp->pdev;

	/* deleted timer */
	del_timer_sync(&lp->timer);

	spin_lock_irq(&lp->lock);
	napi_disable(&lp->napi);
	netif_stop_queue(dev);
	r6040_down(dev);

	free_irq(dev->irq, dev);

	/* Free RX buffer */
	r6040_free_rxbufs(dev);

	/* Free TX buffer */
	r6040_free_txbufs(dev);

	spin_unlock_irq(&lp->lock);

	/* Free Descriptor memory */
	if (lp->rx_ring) {
		pci_free_consistent(pdev, RX_DESC_SIZE, lp->rx_ring, lp->rx_ring_dma);
		lp->rx_ring = NULL;
	}

	if (lp->tx_ring) {
		pci_free_consistent(pdev, TX_DESC_SIZE, lp->tx_ring, lp->tx_ring_dma);
		lp->tx_ring = NULL;
	}

	return 0;
}