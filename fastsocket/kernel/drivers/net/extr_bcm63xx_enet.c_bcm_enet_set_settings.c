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
struct ethtool_cmd {scalar_t__ speed; scalar_t__ port; scalar_t__ duplex; scalar_t__ autoneg; } ;
struct bcm_enet_priv {int force_speed_100; int force_duplex_full; int /*<<< orphan*/  phydev; scalar_t__ has_phy; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  bcm_enet_adjust_link (struct net_device*) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int phy_ethtool_sset (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 

__attribute__((used)) static int bcm_enet_set_settings(struct net_device *dev,
				 struct ethtool_cmd *cmd)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	if (priv->has_phy) {
		if (!priv->phydev)
			return -ENODEV;
		return phy_ethtool_sset(priv->phydev, cmd);
	} else {

		if (cmd->autoneg ||
		    (cmd->speed != SPEED_100 && cmd->speed != SPEED_10) ||
		    cmd->port != PORT_MII)
			return -EINVAL;

		priv->force_speed_100 = (cmd->speed == SPEED_100) ? 1 : 0;
		priv->force_duplex_full = (cmd->duplex == DUPLEX_FULL) ? 1 : 0;

		if (netif_running(dev))
			bcm_enet_adjust_link(dev);
		return 0;
	}
}