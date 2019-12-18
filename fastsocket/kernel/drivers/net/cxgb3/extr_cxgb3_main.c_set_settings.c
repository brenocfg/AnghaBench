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
typedef  scalar_t__ u32 ;
struct link_config {int supported; int advertising; scalar_t__ autoneg; int /*<<< orphan*/  requested_duplex; scalar_t__ requested_speed; } ;
struct port_info {int /*<<< orphan*/  mac; int /*<<< orphan*/  phy; struct link_config link_config; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ autoneg; int advertising; int /*<<< orphan*/  duplex; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MASK ; 
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_INVALID ; 
 int EINVAL ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_INVALID ; 
 int SUPPORTED_Autoneg ; 
 scalar_t__ ethtool_cmd_speed (struct ethtool_cmd*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int speed_duplex_to_caps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_link_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct link_config*) ; 

__attribute__((used)) static int set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct port_info *p = netdev_priv(dev);
	struct link_config *lc = &p->link_config;

	if (!(lc->supported & SUPPORTED_Autoneg)) {
		/*
		 * PHY offers a single speed/duplex.  See if that's what's
		 * being requested.
		 */
		if (cmd->autoneg == AUTONEG_DISABLE) {
			u32 speed = ethtool_cmd_speed(cmd);
			int cap = speed_duplex_to_caps(speed, cmd->duplex);
			if (lc->supported & cap)
				return 0;
		}
		return -EINVAL;
	}

	if (cmd->autoneg == AUTONEG_DISABLE) {
		u32 speed = ethtool_cmd_speed(cmd);
		int cap = speed_duplex_to_caps(speed, cmd->duplex);

		if (!(lc->supported & cap) || (speed == SPEED_1000))
			return -EINVAL;
		lc->requested_speed = speed;
		lc->requested_duplex = cmd->duplex;
		lc->advertising = 0;
	} else {
		cmd->advertising &= ADVERTISED_MASK;
		cmd->advertising &= lc->supported;
		if (!cmd->advertising)
			return -EINVAL;
		lc->requested_speed = SPEED_INVALID;
		lc->requested_duplex = DUPLEX_INVALID;
		lc->advertising = cmd->advertising | ADVERTISED_Autoneg;
	}
	lc->autoneg = cmd->autoneg;
	if (netif_running(dev))
		t3_link_start(&p->phy, &p->mac, lc);
	return 0;
}