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
struct mii_ioctl_data {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct fs_enet_private {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ ,struct mii_ioctl_data*,int) ; 

__attribute__((used)) static int fs_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	struct mii_ioctl_data *mii = (struct mii_ioctl_data *)&rq->ifr_data;

	if (!netif_running(dev))
		return -EINVAL;

	return phy_mii_ioctl(fep->phydev, mii, cmd);
}