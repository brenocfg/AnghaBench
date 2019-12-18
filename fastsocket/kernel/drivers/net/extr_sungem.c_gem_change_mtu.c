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
struct gem {scalar_t__ lstate; int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_lock; scalar_t__ running; } ;

/* Variables and functions */
 int EINVAL ; 
 int GEM_MAX_MTU ; 
 int GEM_MIN_MTU ; 
 int /*<<< orphan*/  gem_reinit_chip (struct gem*) ; 
 int /*<<< orphan*/  gem_set_link_modes (struct gem*) ; 
 scalar_t__ link_up ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gem_change_mtu(struct net_device *dev, int new_mtu)
{
	struct gem *gp = netdev_priv(dev);

	if (new_mtu < GEM_MIN_MTU || new_mtu > GEM_MAX_MTU)
		return -EINVAL;

	if (!netif_running(dev) || !netif_device_present(dev)) {
		/* We'll just catch it later when the
		 * device is up'd or resumed.
		 */
		dev->mtu = new_mtu;
		return 0;
	}

	mutex_lock(&gp->pm_mutex);
	spin_lock_irq(&gp->lock);
	spin_lock(&gp->tx_lock);
	dev->mtu = new_mtu;
	if (gp->running) {
		gem_reinit_chip(gp);
		if (gp->lstate == link_up)
			gem_set_link_modes(gp);
	}
	spin_unlock(&gp->tx_lock);
	spin_unlock_irq(&gp->lock);
	mutex_unlock(&gp->pm_mutex);

	return 0;
}