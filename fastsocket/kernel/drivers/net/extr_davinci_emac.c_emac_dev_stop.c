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
struct resource {int start; int end; } ;
struct device {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; struct device dev; } ;
struct emac_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; scalar_t__ phydev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_DEF_RX_CH ; 
 int /*<<< orphan*/  EMAC_DEF_TX_CH ; 
 int /*<<< orphan*/  EMAC_SOFTRESET ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_cleanup_rxch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_cleanup_txch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_int_disable (struct emac_priv*) ; 
 int /*<<< orphan*/  emac_stop_rxch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_stop_txch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_drv (struct emac_priv*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct resource* platform_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int emac_dev_stop(struct net_device *ndev)
{
	struct resource *res;
	int i = 0;
	int irq_num;
	struct emac_priv *priv = netdev_priv(ndev);
	struct device *emac_dev = &ndev->dev;

	/* inform the upper layers. */
	netif_stop_queue(ndev);
	napi_disable(&priv->napi);

	netif_carrier_off(ndev);
	emac_int_disable(priv);
	emac_stop_txch(priv, EMAC_DEF_TX_CH);
	emac_stop_rxch(priv, EMAC_DEF_RX_CH);
	emac_cleanup_txch(priv, EMAC_DEF_TX_CH);
	emac_cleanup_rxch(priv, EMAC_DEF_RX_CH);
	emac_write(EMAC_SOFTRESET, 1);

	if (priv->phydev)
		phy_disconnect(priv->phydev);

	/* Free IRQ */
	while ((res = platform_get_resource(priv->pdev, IORESOURCE_IRQ, i))) {
		for (irq_num = res->start; irq_num <= res->end; irq_num++)
			free_irq(irq_num, priv->ndev);
		i++;
	}

	if (netif_msg_drv(priv))
		dev_notice(emac_dev, "DaVinci EMAC: %s stopped\n", ndev->name);

	return 0;
}