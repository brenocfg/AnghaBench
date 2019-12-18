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
struct ifreq {int dummy; } ;
struct at91_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  disable_mdi () ; 
 int /*<<< orphan*/  enable_mdi () ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91ether_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct at91_private *lp = netdev_priv(dev);
	int res;

	if (!netif_running(dev))
		return -EINVAL;

	spin_lock_irq(&lp->lock);
	enable_mdi();
	res = generic_mii_ioctl(&lp->mii, if_mii(rq), cmd, NULL);
	disable_mdi();
	spin_unlock_irq(&lp->lock);

	return res;
}