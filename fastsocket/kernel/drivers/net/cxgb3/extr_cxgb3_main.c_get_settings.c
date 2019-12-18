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
struct TYPE_6__ {int supported; int speed; int duplex; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; } ;
struct TYPE_4__ {int /*<<< orphan*/  prtad; } ;
struct TYPE_5__ {TYPE_1__ mdio; } ;
struct port_info {TYPE_3__ link_config; TYPE_2__ phy; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int duplex; scalar_t__ maxrxpkt; scalar_t__ maxtxpkt; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct port_info *p = netdev_priv(dev);

	cmd->supported = p->link_config.supported;
	cmd->advertising = p->link_config.advertising;

	if (netif_carrier_ok(dev)) {
		ethtool_cmd_speed_set(cmd, p->link_config.speed);
		cmd->duplex = p->link_config.duplex;
	} else {
		ethtool_cmd_speed_set(cmd, -1);
		cmd->duplex = -1;
	}

	cmd->port = (cmd->supported & SUPPORTED_TP) ? PORT_TP : PORT_FIBRE;
	cmd->phy_address = p->phy.mdio.prtad;
	cmd->transceiver = XCVR_EXTERNAL;
	cmd->autoneg = p->link_config.autoneg;
	cmd->maxtxpkt = 0;
	cmd->maxrxpkt = 0;
	return 0;
}