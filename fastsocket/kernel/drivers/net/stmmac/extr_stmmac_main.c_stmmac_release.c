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
struct stmmac_priv {int /*<<< orphan*/  rx_recycle; int /*<<< orphan*/  napi; int /*<<< orphan*/ * tm; int /*<<< orphan*/ * phydev; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dma_desc_resources (struct stmmac_priv*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_close_ext_timer () ; 
 int /*<<< orphan*/  stmmac_dma_stop_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_dma_stop_tx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_mac_disable_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_mac_disable_tx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_release(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	/* Stop and disconnect the PHY */
	if (priv->phydev) {
		phy_stop(priv->phydev);
		phy_disconnect(priv->phydev);
		priv->phydev = NULL;
	}

	netif_stop_queue(dev);

#ifdef CONFIG_STMMAC_TIMER
	/* Stop and release the timer */
	stmmac_close_ext_timer();
	if (priv->tm != NULL)
		kfree(priv->tm);
#endif
	napi_disable(&priv->napi);
	skb_queue_purge(&priv->rx_recycle);

	/* Free the IRQ lines */
	free_irq(dev->irq, dev);

	/* Stop TX/RX DMA and clear the descriptors */
	stmmac_dma_stop_tx(dev->base_addr);
	stmmac_dma_stop_rx(dev->base_addr);

	/* Release and free the Rx/Tx resources */
	free_dma_desc_resources(priv);

	/* Disable the MAC core */
	stmmac_mac_disable_tx(dev->base_addr);
	stmmac_mac_disable_rx(dev->base_addr);

	netif_carrier_off(dev);

	return 0;
}