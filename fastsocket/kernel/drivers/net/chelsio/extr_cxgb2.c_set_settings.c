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
struct link_config {int supported; scalar_t__ requested_speed; int advertising; scalar_t__ autoneg; int /*<<< orphan*/  requested_duplex; } ;
struct port_info {int /*<<< orphan*/  mac; int /*<<< orphan*/  phy; struct link_config link_config; } ;
struct net_device {size_t if_port; struct adapter* ml_priv; } ;
struct ethtool_cmd {scalar_t__ autoneg; scalar_t__ speed; int advertising; int /*<<< orphan*/  duplex; } ;
struct adapter {struct port_info* port; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MASK ; 
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_INVALID ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_INVALID ; 
 int SUPPORTED_Autoneg ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int speed_duplex_to_caps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_link_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_config*) ; 

__attribute__((used)) static int set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct adapter *adapter = dev->ml_priv;
	struct port_info *p = &adapter->port[dev->if_port];
	struct link_config *lc = &p->link_config;

	if (!(lc->supported & SUPPORTED_Autoneg))
		return -EOPNOTSUPP;             /* can't change speed/duplex */

	if (cmd->autoneg == AUTONEG_DISABLE) {
		int cap = speed_duplex_to_caps(cmd->speed, cmd->duplex);

		if (!(lc->supported & cap) || cmd->speed == SPEED_1000)
			return -EINVAL;
		lc->requested_speed = cmd->speed;
		lc->requested_duplex = cmd->duplex;
		lc->advertising = 0;
	} else {
		cmd->advertising &= ADVERTISED_MASK;
		if (cmd->advertising & (cmd->advertising - 1))
			cmd->advertising = lc->supported;
		cmd->advertising &= lc->supported;
		if (!cmd->advertising)
			return -EINVAL;
		lc->requested_speed = SPEED_INVALID;
		lc->requested_duplex = DUPLEX_INVALID;
		lc->advertising = cmd->advertising | ADVERTISED_Autoneg;
	}
	lc->autoneg = cmd->autoneg;
	if (netif_running(dev))
		t1_link_start(p->phy, p->mac, lc);
	return 0;
}