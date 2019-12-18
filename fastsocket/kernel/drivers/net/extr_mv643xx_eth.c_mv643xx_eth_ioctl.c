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
struct mv643xx_eth_private {int /*<<< orphan*/ * phy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv643xx_eth_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);

	if (mp->phy != NULL)
		return phy_mii_ioctl(mp->phy, if_mii(ifr), cmd);

	return -EOPNOTSUPP;
}