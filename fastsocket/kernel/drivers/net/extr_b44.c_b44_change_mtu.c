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
struct b44 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_FULL_RESET ; 
 int B44_MAX_MTU ; 
 int B44_MIN_MTU ; 
 int EINVAL ; 
 int /*<<< orphan*/  b44_enable_ints (struct b44*) ; 
 int /*<<< orphan*/  b44_halt (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_init_rings (struct b44*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b44_change_mtu(struct net_device *dev, int new_mtu)
{
	struct b44 *bp = netdev_priv(dev);

	if (new_mtu < B44_MIN_MTU || new_mtu > B44_MAX_MTU)
		return -EINVAL;

	if (!netif_running(dev)) {
		/* We'll just catch it later when the
		 * device is up'd.
		 */
		dev->mtu = new_mtu;
		return 0;
	}

	spin_lock_irq(&bp->lock);
	b44_halt(bp);
	dev->mtu = new_mtu;
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);
	spin_unlock_irq(&bp->lock);

	b44_enable_ints(bp);

	return 0;
}