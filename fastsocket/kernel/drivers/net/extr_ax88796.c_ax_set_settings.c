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
struct ethtool_cmd {int dummy; } ;
struct ax_device {int /*<<< orphan*/  mii_lock; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static int ax_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ax_device *ax = to_ax_dev(dev);
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&ax->mii_lock, flags);
	rc = mii_ethtool_sset(&ax->mii, cmd);
	spin_unlock_irqrestore(&ax->mii_lock, flags);

	return rc;
}