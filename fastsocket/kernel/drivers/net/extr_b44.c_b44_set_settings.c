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
struct ethtool_cmd {scalar_t__ autoneg; int advertising; scalar_t__ speed; scalar_t__ duplex; } ;
struct b44 {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int B44_FLAG_100_BASE_T ; 
 int B44_FLAG_ADV_100FULL ; 
 int B44_FLAG_ADV_100HALF ; 
 int B44_FLAG_ADV_10FULL ; 
 int B44_FLAG_ADV_10HALF ; 
 int B44_FLAG_FORCE_LINK ; 
 int B44_FLAG_FULL_DUPLEX ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  b44_setup_phy (struct b44*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b44_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct b44 *bp = netdev_priv(dev);

	/* We do not support gigabit. */
	if (cmd->autoneg == AUTONEG_ENABLE) {
		if (cmd->advertising &
		    (ADVERTISED_1000baseT_Half |
		     ADVERTISED_1000baseT_Full))
			return -EINVAL;
	} else if ((cmd->speed != SPEED_100 &&
		    cmd->speed != SPEED_10) ||
		   (cmd->duplex != DUPLEX_HALF &&
		    cmd->duplex != DUPLEX_FULL)) {
			return -EINVAL;
	}

	spin_lock_irq(&bp->lock);

	if (cmd->autoneg == AUTONEG_ENABLE) {
		bp->flags &= ~(B44_FLAG_FORCE_LINK |
			       B44_FLAG_100_BASE_T |
			       B44_FLAG_FULL_DUPLEX |
			       B44_FLAG_ADV_10HALF |
			       B44_FLAG_ADV_10FULL |
			       B44_FLAG_ADV_100HALF |
			       B44_FLAG_ADV_100FULL);
		if (cmd->advertising == 0) {
			bp->flags |= (B44_FLAG_ADV_10HALF |
				      B44_FLAG_ADV_10FULL |
				      B44_FLAG_ADV_100HALF |
				      B44_FLAG_ADV_100FULL);
		} else {
			if (cmd->advertising & ADVERTISED_10baseT_Half)
				bp->flags |= B44_FLAG_ADV_10HALF;
			if (cmd->advertising & ADVERTISED_10baseT_Full)
				bp->flags |= B44_FLAG_ADV_10FULL;
			if (cmd->advertising & ADVERTISED_100baseT_Half)
				bp->flags |= B44_FLAG_ADV_100HALF;
			if (cmd->advertising & ADVERTISED_100baseT_Full)
				bp->flags |= B44_FLAG_ADV_100FULL;
		}
	} else {
		bp->flags |= B44_FLAG_FORCE_LINK;
		bp->flags &= ~(B44_FLAG_100_BASE_T | B44_FLAG_FULL_DUPLEX);
		if (cmd->speed == SPEED_100)
			bp->flags |= B44_FLAG_100_BASE_T;
		if (cmd->duplex == DUPLEX_FULL)
			bp->flags |= B44_FLAG_FULL_DUPLEX;
	}

	if (netif_running(dev))
		b44_setup_phy(bp);

	spin_unlock_irq(&bp->lock);

	return 0;
}