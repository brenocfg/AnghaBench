#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  mem_start; } ;
struct ethoc {int /*<<< orphan*/  membase; scalar_t__ dma_alloc; TYPE_1__* mdio; int /*<<< orphan*/ * phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_1__*) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ethoc_remove(struct platform_device *pdev)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	struct ethoc *priv = netdev_priv(netdev);

	platform_set_drvdata(pdev, NULL);

	if (netdev) {
		phy_disconnect(priv->phy);
		priv->phy = NULL;

		if (priv->mdio) {
			mdiobus_unregister(priv->mdio);
			kfree(priv->mdio->irq);
			mdiobus_free(priv->mdio);
		}
		if (priv->dma_alloc)
			dma_free_coherent(NULL, priv->dma_alloc, priv->membase,
				netdev->mem_start);
		unregister_netdev(netdev);
		free_netdev(netdev);
	}

	return 0;
}