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
struct net_device {int dummy; } ;
struct gfar_private {struct phy_device* phydev; } ;
struct ethtool_cmd {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int phy_ethtool_sset (struct phy_device*,struct ethtool_cmd*) ; 

__attribute__((used)) static int gfar_ssettings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct gfar_private *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;

	if (NULL == phydev)
		return -ENODEV;

	return phy_ethtool_sset(phydev, cmd);
}