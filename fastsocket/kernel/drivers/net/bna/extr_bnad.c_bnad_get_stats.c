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
struct net_device {struct net_device_stats stats; } ;
struct bnad {int /*<<< orphan*/  bna_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnad_netdev_hwstats_fill (struct bnad*,struct net_device_stats*) ; 
 int /*<<< orphan*/  bnad_netdev_qstats_fill (struct bnad*,struct net_device_stats*) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct net_device_stats *
bnad_get_stats(struct net_device *netdev)
{
	struct bnad *bnad = netdev_priv(netdev);
	struct net_device_stats *stats = &netdev->stats;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	bnad_netdev_qstats_fill(bnad, stats);
	bnad_netdev_hwstats_fill(bnad, stats);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	return stats;
}