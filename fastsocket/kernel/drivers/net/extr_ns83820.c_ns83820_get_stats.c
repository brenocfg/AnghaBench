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
struct net_device_stats {int dummy; } ;
struct ns83820 {struct net_device_stats stats; int /*<<< orphan*/  misc_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ns83820* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  ns83820_update_stats (struct ns83820*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *ns83820_get_stats(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);

	/* somewhat overkill */
	spin_lock_irq(&dev->misc_lock);
	ns83820_update_stats(dev);
	spin_unlock_irq(&dev->misc_lock);

	return &dev->stats;
}