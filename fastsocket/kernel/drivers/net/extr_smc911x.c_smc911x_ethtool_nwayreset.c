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
struct smc911x_local {scalar_t__ phy_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct smc911x_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smc911x_ethtool_nwayreset(struct net_device *dev)
{
	struct smc911x_local *lp = netdev_priv(dev);
	int ret = -EINVAL;
	unsigned long flags;

	if (lp->phy_type != 0) {
		spin_lock_irqsave(&lp->lock, flags);
		ret = mii_nway_restart(&lp->mii);
		spin_unlock_irqrestore(&lp->lock, flags);
	}

	return ret;
}