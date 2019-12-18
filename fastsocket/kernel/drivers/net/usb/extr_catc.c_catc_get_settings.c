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
struct ethtool_cmd {int supported; int advertising; int maxtxpkt; int maxrxpkt; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct catc {int /*<<< orphan*/  is_f5u011; } ;

/* Variables and functions */
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 struct catc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int catc_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct catc *catc = netdev_priv(dev);
	if (!catc->is_f5u011)
		return -EOPNOTSUPP;

	cmd->supported = SUPPORTED_10baseT_Half | SUPPORTED_TP;
	cmd->advertising = ADVERTISED_10baseT_Half | ADVERTISED_TP;
	cmd->speed = SPEED_10;
	cmd->duplex = DUPLEX_HALF;
	cmd->port = PORT_TP; 
	cmd->phy_address = 0;
	cmd->transceiver = XCVR_INTERNAL;
	cmd->autoneg = AUTONEG_DISABLE;
	cmd->maxtxpkt = 1;
	cmd->maxrxpkt = 1;
	return 0;
}