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
struct bfin_mac_local {scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct bfin_mac_local* netdev_priv (struct net_device*) ; 
 int phy_ethtool_sset (scalar_t__,struct ethtool_cmd*) ; 

__attribute__((used)) static int
bfin_mac_ethtool_setsettings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct bfin_mac_local *lp = netdev_priv(dev);

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (lp->phydev)
		return phy_ethtool_sset(lp->phydev, cmd);

	return -EINVAL;
}