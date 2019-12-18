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
struct iss_net_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 struct iss_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iss_net_change_mtu(struct net_device *dev, int new_mtu)
{
#if 0
	struct iss_net_private *lp = netdev_priv(dev);
	int err = 0;

	spin_lock(&lp->lock);

	// FIXME not needed new_mtu = transport_set_mtu(new_mtu, &lp->user);

	if (new_mtu < 0)
		err = new_mtu;
	else
		dev->mtu = new_mtu;

	spin_unlock(&lp->lock);
	return err;
#endif
	return -EINVAL;
}