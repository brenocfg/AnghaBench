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
struct ethtool_cmd {int duplex; scalar_t__ maxrxpkt; scalar_t__ maxtxpkt; int /*<<< orphan*/  transceiver; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  SUPPORTED_10000baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int
bnad_get_settings(struct net_device *netdev, struct ethtool_cmd *cmd)
{
	cmd->supported = SUPPORTED_10000baseT_Full;
	cmd->advertising = ADVERTISED_10000baseT_Full;
	cmd->autoneg = AUTONEG_DISABLE;
	cmd->supported |= SUPPORTED_FIBRE;
	cmd->advertising |= ADVERTISED_FIBRE;
	cmd->port = PORT_FIBRE;
	cmd->phy_address = 0;

	if (netif_carrier_ok(netdev)) {
		ethtool_cmd_speed_set(cmd, SPEED_10000);
		cmd->duplex = DUPLEX_FULL;
	} else {
		ethtool_cmd_speed_set(cmd, -1);
		cmd->duplex = -1;
	}
	cmd->transceiver = XCVR_EXTERNAL;
	cmd->maxtxpkt = 0;
	cmd->maxrxpkt = 0;

	return 0;
}