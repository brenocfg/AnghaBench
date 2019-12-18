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
struct korina_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct korina_private *lp = netdev_priv(dev);
	int rc;

	spin_lock_irq(&lp->lock);
	rc = mii_ethtool_gset(&lp->mii_if, cmd);
	spin_unlock_irq(&lp->lock);

	return rc;
}