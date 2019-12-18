#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {size_t phy_id; } ;
struct ifreq {int dummy; } ;
struct ethoc {struct phy_device* phy; TYPE_1__* mdio; } ;
struct TYPE_2__ {struct phy_device** phy_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 size_t PHY_MAX_ADDR ; 
 int SIOCGMIIPHY ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (struct phy_device*,struct mii_ioctl_data*,int) ; 

__attribute__((used)) static int ethoc_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct ethoc *priv = netdev_priv(dev);
	struct mii_ioctl_data *mdio = if_mii(ifr);
	struct phy_device *phy = NULL;

	if (!netif_running(dev))
		return -EINVAL;

	if (cmd != SIOCGMIIPHY) {
		if (mdio->phy_id >= PHY_MAX_ADDR)
			return -ERANGE;

		phy = priv->mdio->phy_map[mdio->phy_id];
		if (!phy)
			return -ENODEV;
	} else {
		phy = priv->phy;
	}

	return phy_mii_ioctl(phy, mdio, cmd);
}