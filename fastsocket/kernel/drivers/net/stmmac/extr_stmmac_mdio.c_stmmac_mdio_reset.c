#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {int /*<<< orphan*/  bsp_priv; int /*<<< orphan*/  (* phy_reset ) (int /*<<< orphan*/ ) ;TYPE_3__* mac_type; } ;
struct net_device {unsigned long base_addr; } ;
struct mii_bus {struct net_device* priv; } ;
struct TYPE_4__ {unsigned int addr; } ;
struct TYPE_5__ {TYPE_1__ mii; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int stmmac_mdio_reset(struct mii_bus *bus)
{
	struct net_device *ndev = bus->priv;
	struct stmmac_priv *priv = netdev_priv(ndev);
	unsigned long ioaddr = ndev->base_addr;
	unsigned int mii_address = priv->mac_type->hw.mii.addr;

	if (priv->phy_reset) {
		pr_debug("stmmac_mdio_reset: calling phy_reset\n");
		priv->phy_reset(priv->bsp_priv);
	}

	/* This is a workaround for problems with the STE101P PHY.
	 * It doesn't complete its reset until at least one clock cycle
	 * on MDC, so perform a dummy mdio read.
	 */
	writel(0, ioaddr + mii_address);

	return 0;
}