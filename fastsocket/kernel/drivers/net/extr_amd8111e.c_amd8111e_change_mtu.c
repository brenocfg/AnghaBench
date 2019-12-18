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
struct net_device {int mtu; } ;
struct amd8111e_priv {int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 int AMD8111E_MAX_MTU ; 
 int AMD8111E_MIN_MTU ; 
 scalar_t__ CMD0 ; 
 int EINVAL ; 
 int /*<<< orphan*/  RUN ; 
 int amd8111e_restart (struct net_device*) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int amd8111e_change_mtu(struct net_device *dev, int new_mtu)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	int err;

	if ((new_mtu < AMD8111E_MIN_MTU) || (new_mtu > AMD8111E_MAX_MTU))
		return -EINVAL;

	if (!netif_running(dev)) {
		/* new_mtu will be used
		   when device starts netxt time */
		dev->mtu = new_mtu;
		return 0;
	}

	spin_lock_irq(&lp->lock);

        /* stop the chip */
	writel(RUN, lp->mmio + CMD0);

	dev->mtu = new_mtu;

	err = amd8111e_restart(dev);
	spin_unlock_irq(&lp->lock);
	if(!err)
		netif_start_queue(dev);
	return err;
}