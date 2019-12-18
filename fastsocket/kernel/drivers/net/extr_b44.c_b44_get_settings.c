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
struct ethtool_cmd {int supported; int advertising; int duplex; scalar_t__ autoneg; scalar_t__ maxrxpkt; scalar_t__ maxtxpkt; scalar_t__ speed; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  phy_address; scalar_t__ port; } ;
struct b44 {int flags; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_Pause ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int B44_FLAG_100_BASE_T ; 
 int B44_FLAG_ADV_100FULL ; 
 int B44_FLAG_ADV_100HALF ; 
 int B44_FLAG_ADV_10FULL ; 
 int B44_FLAG_ADV_10HALF ; 
 int B44_FLAG_FORCE_LINK ; 
 int B44_FLAG_FULL_DUPLEX ; 
 int B44_FLAG_INTERNAL_PHY ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int b44_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct b44 *bp = netdev_priv(dev);

	cmd->supported = (SUPPORTED_Autoneg);
	cmd->supported |= (SUPPORTED_100baseT_Half |
			  SUPPORTED_100baseT_Full |
			  SUPPORTED_10baseT_Half |
			  SUPPORTED_10baseT_Full |
			  SUPPORTED_MII);

	cmd->advertising = 0;
	if (bp->flags & B44_FLAG_ADV_10HALF)
		cmd->advertising |= ADVERTISED_10baseT_Half;
	if (bp->flags & B44_FLAG_ADV_10FULL)
		cmd->advertising |= ADVERTISED_10baseT_Full;
	if (bp->flags & B44_FLAG_ADV_100HALF)
		cmd->advertising |= ADVERTISED_100baseT_Half;
	if (bp->flags & B44_FLAG_ADV_100FULL)
		cmd->advertising |= ADVERTISED_100baseT_Full;
	cmd->advertising |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;
	cmd->speed = (bp->flags & B44_FLAG_100_BASE_T) ?
		SPEED_100 : SPEED_10;
	cmd->duplex = (bp->flags & B44_FLAG_FULL_DUPLEX) ?
		DUPLEX_FULL : DUPLEX_HALF;
	cmd->port = 0;
	cmd->phy_address = bp->phy_addr;
	cmd->transceiver = (bp->flags & B44_FLAG_INTERNAL_PHY) ?
		XCVR_INTERNAL : XCVR_EXTERNAL;
	cmd->autoneg = (bp->flags & B44_FLAG_FORCE_LINK) ?
		AUTONEG_DISABLE : AUTONEG_ENABLE;
	if (cmd->autoneg == AUTONEG_ENABLE)
		cmd->advertising |= ADVERTISED_Autoneg;
	if (!netif_running(dev)){
		cmd->speed = 0;
		cmd->duplex = 0xff;
	}
	cmd->maxtxpkt = 0;
	cmd->maxrxpkt = 0;
	return 0;
}