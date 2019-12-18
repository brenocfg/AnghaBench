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
struct ethtool_cmd {int supported; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; scalar_t__ advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ autoneg; scalar_t__ maxtxpkt; scalar_t__ maxrxpkt; } ;
struct bcm_enet_priv {scalar_t__ force_duplex_full; scalar_t__ force_speed_100; int /*<<< orphan*/  phydev; scalar_t__ has_phy; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int ENODEV ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int phy_ethtool_gset (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 

__attribute__((used)) static int bcm_enet_get_settings(struct net_device *dev,
				 struct ethtool_cmd *cmd)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	cmd->maxrxpkt = 0;
	cmd->maxtxpkt = 0;

	if (priv->has_phy) {
		if (!priv->phydev)
			return -ENODEV;
		return phy_ethtool_gset(priv->phydev, cmd);
	} else {
		cmd->autoneg = 0;
		cmd->speed = (priv->force_speed_100) ? SPEED_100 : SPEED_10;
		cmd->duplex = (priv->force_duplex_full) ?
			DUPLEX_FULL : DUPLEX_HALF;
		cmd->supported = ADVERTISED_10baseT_Half  |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full;
		cmd->advertising = 0;
		cmd->port = PORT_MII;
		cmd->transceiver = XCVR_EXTERNAL;
	}
	return 0;
}