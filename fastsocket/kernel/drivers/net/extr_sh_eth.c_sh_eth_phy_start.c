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
struct sh_eth_private {int /*<<< orphan*/  phydev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sh_eth_phy_init (struct net_device*) ; 

__attribute__((used)) static int sh_eth_phy_start(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int ret;

	ret = sh_eth_phy_init(ndev);
	if (ret)
		return ret;

	/* reset phy - this also wakes it from PDOWN */
	phy_write(mdp->phydev, MII_BMCR, BMCR_RESET);
	phy_start(mdp->phydev);

	return 0;
}