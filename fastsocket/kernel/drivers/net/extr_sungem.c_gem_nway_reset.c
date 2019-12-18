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
struct gem {int /*<<< orphan*/  lock; int /*<<< orphan*/  want_autoneg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gem_begin_auto_negotiation (struct gem*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gem_get_cell (struct gem*) ; 
 int /*<<< orphan*/  gem_put_cell (struct gem*) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gem_nway_reset(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);

	if (!gp->want_autoneg)
		return -EINVAL;

	/* Restart link process. */
	spin_lock_irq(&gp->lock);
	gem_get_cell(gp);
	gem_begin_auto_negotiation(gp, NULL);
	gem_put_cell(gp);
	spin_unlock_irq(&gp->lock);

	return 0;
}