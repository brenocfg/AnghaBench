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
struct netdev_private {scalar_t__* phys; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii_if; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {scalar_t__ phy_id; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIOCSMIIREG ; 
 int /*<<< orphan*/  check_duplex (struct net_device*) ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int,int /*<<< orphan*/ *) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct netdev_private *np = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(rq);
	int rc;

	if (!netif_running(dev))
		return -EINVAL;

	spin_lock_irq(&np->lock);
	rc = generic_mii_ioctl(&np->mii_if, data, cmd, NULL);
	spin_unlock_irq(&np->lock);

	if ((cmd == SIOCSMIIREG) && (data->phy_id == np->phys[0]))
		check_duplex(dev);

	return rc;
}