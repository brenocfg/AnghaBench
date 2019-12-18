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
struct gem {int wake_on_lan; int /*<<< orphan*/  has_wol; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WOL_SUPPORTED_MASK ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gem_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct gem *gp = netdev_priv(dev);

	if (!gp->has_wol)
		return -EOPNOTSUPP;
	gp->wake_on_lan = wol->wolopts & WOL_SUPPORTED_MASK;
	return 0;
}