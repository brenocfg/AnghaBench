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
struct phy_device {int dummy; } ;
struct pasemi_mac {struct phy_device* phydev; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct pasemi_mac* netdev_priv (struct net_device*) ; 
 int phy_ethtool_gset (struct phy_device*,struct ethtool_cmd*) ; 

__attribute__((used)) static int
pasemi_mac_ethtool_get_settings(struct net_device *netdev,
			       struct ethtool_cmd *cmd)
{
	struct pasemi_mac *mac = netdev_priv(netdev);
	struct phy_device *phydev = mac->phydev;

	if (!phydev)
		return -EOPNOTSUPP;

	return phy_ethtool_gset(phydev, cmd);
}