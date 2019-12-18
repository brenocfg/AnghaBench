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
struct w90p910_ether {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int generic_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int,int /*<<< orphan*/ *) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int w90p910_ether_ioctl(struct net_device *dev,
						struct ifreq *ifr, int cmd)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(ifr);

	return generic_mii_ioctl(&ether->mii, data, cmd, NULL);
}