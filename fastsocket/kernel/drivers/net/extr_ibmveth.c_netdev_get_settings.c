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
struct ethtool_cmd {int supported; int advertising; int maxrxpkt; scalar_t__ maxtxpkt; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 

__attribute__((used)) static int netdev_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	cmd->supported = (SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg |
				SUPPORTED_FIBRE);
	cmd->advertising = (ADVERTISED_1000baseT_Full | ADVERTISED_Autoneg |
				ADVERTISED_FIBRE);
	cmd->speed = SPEED_1000;
	cmd->duplex = DUPLEX_FULL;
	cmd->port = PORT_FIBRE;
	cmd->phy_address = 0;
	cmd->transceiver = XCVR_INTERNAL;
	cmd->autoneg = AUTONEG_ENABLE;
	cmd->maxtxpkt = 0;
	cmd->maxrxpkt = 1;
	return 0;
}