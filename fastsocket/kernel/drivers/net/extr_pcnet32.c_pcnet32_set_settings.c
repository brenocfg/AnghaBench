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
struct pcnet32_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; scalar_t__ mii; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcnet32_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	unsigned long flags;
	int r = -EOPNOTSUPP;

	if (lp->mii) {
		spin_lock_irqsave(&lp->lock, flags);
		r = mii_ethtool_sset(&lp->mii_if, cmd);
		spin_unlock_irqrestore(&lp->lock, flags);
	}
	return r;
}