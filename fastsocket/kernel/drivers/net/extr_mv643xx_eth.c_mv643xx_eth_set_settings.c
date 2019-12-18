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
struct net_device {int dummy; } ;
struct mv643xx_eth_private {int /*<<< orphan*/ * phy; } ;
struct ethtool_cmd {int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_1000baseT_Half ; 
 int EINVAL ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int phy_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 

__attribute__((used)) static int
mv643xx_eth_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	if (mp->phy == NULL)
		return -EINVAL;

	/*
	 * The MAC does not support 1000baseT_Half.
	 */
	cmd->advertising &= ~ADVERTISED_1000baseT_Half;

	return phy_ethtool_sset(mp->phy, cmd);
}