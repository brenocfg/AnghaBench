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
typedef  scalar_t__ u32 ;
struct sh_eth_txdesc {int dummy; } ;
struct sh_eth_rxdesc {int dummy; } ;
struct sh_eth_private {int /*<<< orphan*/  tx_desc_dma; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_desc_dma; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  timer; scalar_t__ phydev; } ;
struct net_device {int /*<<< orphan*/  irq; scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ EDRRR ; 
 scalar_t__ EDTRR ; 
 scalar_t__ EESIPR ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  ctrl_outl (int,scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  sh_eth_ring_free (struct net_device*) ; 

__attribute__((used)) static int sh_eth_close(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	u32 ioaddr = ndev->base_addr;
	int ringsize;

	netif_stop_queue(ndev);

	/* Disable interrupts by clearing the interrupt mask. */
	ctrl_outl(0x0000, ioaddr + EESIPR);

	/* Stop the chip's Tx and Rx processes. */
	ctrl_outl(0, ioaddr + EDTRR);
	ctrl_outl(0, ioaddr + EDRRR);

	/* PHY Disconnect */
	if (mdp->phydev) {
		phy_stop(mdp->phydev);
		phy_disconnect(mdp->phydev);
	}

	free_irq(ndev->irq, ndev);

	del_timer_sync(&mdp->timer);

	/* Free all the skbuffs in the Rx queue. */
	sh_eth_ring_free(ndev);

	/* free DMA buffer */
	ringsize = sizeof(struct sh_eth_rxdesc) * RX_RING_SIZE;
	dma_free_coherent(NULL, ringsize, mdp->rx_ring, mdp->rx_desc_dma);

	/* free DMA buffer */
	ringsize = sizeof(struct sh_eth_txdesc) * TX_RING_SIZE;
	dma_free_coherent(NULL, ringsize, mdp->tx_ring, mdp->tx_desc_dma);

	return 0;
}