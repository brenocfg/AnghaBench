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
struct smc911x_local {scalar_t__ phy_type; int ctl_rfduplx; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ PORT_AUI ; 
 scalar_t__ PORT_TP ; 
 scalar_t__ SPEED_10 ; 
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct smc911x_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
smc911x_ethtool_setsettings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct smc911x_local *lp = netdev_priv(dev);
	int ret;
	unsigned long flags;

	if (lp->phy_type != 0) {
		spin_lock_irqsave(&lp->lock, flags);
		ret = mii_ethtool_sset(&lp->mii, cmd);
		spin_unlock_irqrestore(&lp->lock, flags);
	} else {
		if (cmd->autoneg != AUTONEG_DISABLE ||
			cmd->speed != SPEED_10 ||
			(cmd->duplex != DUPLEX_HALF && cmd->duplex != DUPLEX_FULL) ||
			(cmd->port != PORT_TP && cmd->port != PORT_AUI))
			return -EINVAL;

		lp->ctl_rfduplx = cmd->duplex == DUPLEX_FULL;

		ret = 0;
	}

	return ret;
}