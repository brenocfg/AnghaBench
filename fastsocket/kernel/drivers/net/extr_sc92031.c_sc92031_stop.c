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
struct sc92031_priv {int /*<<< orphan*/  rx_ring_dma_addr; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_bufs_dma_addr; int /*<<< orphan*/  tx_bufs; int /*<<< orphan*/  lock; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_BUF_LEN ; 
 int /*<<< orphan*/  TX_BUF_TOT_LEN ; 
 int /*<<< orphan*/  _sc92031_disable_tx_rx (struct net_device*) ; 
 int /*<<< orphan*/  _sc92031_tx_clear (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 struct sc92031_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc92031_disable_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc92031_stop(struct net_device *dev)
{
	struct sc92031_priv *priv = netdev_priv(dev);
	struct pci_dev *pdev = priv->pdev;

	netif_tx_disable(dev);

	/* Disable interrupts, stop Tx and Rx. */
	sc92031_disable_interrupts(dev);

	spin_lock_bh(&priv->lock);

	_sc92031_disable_tx_rx(dev);
	_sc92031_tx_clear(dev);
	mmiowb();

	spin_unlock_bh(&priv->lock);

	free_irq(pdev->irq, dev);
	pci_free_consistent(pdev, TX_BUF_TOT_LEN, priv->tx_bufs,
			priv->tx_bufs_dma_addr);
	pci_free_consistent(pdev, RX_BUF_LEN, priv->rx_ring,
			priv->rx_ring_dma_addr);

	return 0;
}