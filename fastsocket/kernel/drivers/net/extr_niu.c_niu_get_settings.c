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
struct niu_link_config {int /*<<< orphan*/  active_duplex; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_autoneg; int /*<<< orphan*/  active_advertising; int /*<<< orphan*/  supported; } ;
struct niu {int flags; int /*<<< orphan*/  phy_addr; struct niu_link_config link_config; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; int /*<<< orphan*/  phy_address; } ;

/* Variables and functions */
 int NIU_FLAGS_FIBER ; 
 int NIU_FLAGS_XCVR_SERDES ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int /*<<< orphan*/  memset (struct ethtool_cmd*,int /*<<< orphan*/ ,int) ; 
 struct niu* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int niu_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct niu *np = netdev_priv(dev);
	struct niu_link_config *lp;

	lp = &np->link_config;

	memset(cmd, 0, sizeof(*cmd));
	cmd->phy_address = np->phy_addr;
	cmd->supported = lp->supported;
	cmd->advertising = lp->active_advertising;
	cmd->autoneg = lp->active_autoneg;
	cmd->speed = lp->active_speed;
	cmd->duplex = lp->active_duplex;
	cmd->port = (np->flags & NIU_FLAGS_FIBER) ? PORT_FIBRE : PORT_TP;
	cmd->transceiver = (np->flags & NIU_FLAGS_XCVR_SERDES) ?
		XCVR_EXTERNAL : XCVR_INTERNAL;

	return 0;
}