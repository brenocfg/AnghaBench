#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct link_config {unsigned int supported; unsigned int requested_speed; unsigned int advertising; scalar_t__ autoneg; } ;
struct port_info {int /*<<< orphan*/  tx_chan; TYPE_1__* adapter; struct link_config link_cfg; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ duplex; scalar_t__ autoneg; int /*<<< orphan*/  advertising; } ;
struct TYPE_2__ {int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 unsigned int FW_PORT_CAP_ANEG ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 scalar_t__ ethtool_cmd_speed (struct ethtool_cmd*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 unsigned int speed_to_caps (scalar_t__) ; 
 int t4_link_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_config*) ; 
 unsigned int to_fw_linkcaps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	unsigned int cap;
	struct port_info *p = netdev_priv(dev);
	struct link_config *lc = &p->link_cfg;
	u32 speed = ethtool_cmd_speed(cmd);

	if (cmd->duplex != DUPLEX_FULL)     /* only full-duplex supported */
		return -EINVAL;

	if (!(lc->supported & FW_PORT_CAP_ANEG)) {
		/*
		 * PHY offers a single speed.  See if that's what's
		 * being requested.
		 */
		if (cmd->autoneg == AUTONEG_DISABLE &&
		    (lc->supported & speed_to_caps(speed)))
			return 0;
		return -EINVAL;
	}

	if (cmd->autoneg == AUTONEG_DISABLE) {
		cap = speed_to_caps(speed);

		if (!(lc->supported & cap) || (speed == SPEED_1000) ||
		    (speed == SPEED_10000))
			return -EINVAL;
		lc->requested_speed = cap;
		lc->advertising = 0;
	} else {
		cap = to_fw_linkcaps(cmd->advertising);
		if (!(lc->supported & cap))
			return -EINVAL;
		lc->requested_speed = 0;
		lc->advertising = cap | FW_PORT_CAP_ANEG;
	}
	lc->autoneg = cmd->autoneg;

	if (netif_running(dev))
		return t4_link_start(p->adapter, p->adapter->fn, p->tx_chan,
				     lc);
	return 0;
}