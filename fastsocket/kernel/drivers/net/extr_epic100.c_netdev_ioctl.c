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
struct net_device {long base_addr; } ;
struct mii_ioctl_data {int dummy; } ;
struct ifreq {int dummy; } ;
struct epic_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 scalar_t__ GENCTL ; 
 scalar_t__ NVCTL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,struct mii_ioctl_data*,int,int /*<<< orphan*/ *) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int inl (scalar_t__) ; 
 struct epic_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct epic_private *np = netdev_priv(dev);
	long ioaddr = dev->base_addr;
	struct mii_ioctl_data *data = if_mii(rq);
	int rc;

	/* power-up, if interface is down */
	if (! netif_running(dev)) {
		outl(0x0200, ioaddr + GENCTL);
		outl((inl(ioaddr + NVCTL) & ~0x003C) | 0x4800, ioaddr + NVCTL);
	}

	/* all non-ethtool ioctls (the SIOC[GS]MIIxxx ioctls) */
	spin_lock_irq(&np->lock);
	rc = generic_mii_ioctl(&np->mii, data, cmd, NULL);
	spin_unlock_irq(&np->lock);

	/* power-down, if interface is down */
	if (! netif_running(dev)) {
		outl(0x0008, ioaddr + GENCTL);
		outl((inl(ioaddr + NVCTL) & ~0x483C) | 0x0000, ioaddr + NVCTL);
	}
	return rc;
}