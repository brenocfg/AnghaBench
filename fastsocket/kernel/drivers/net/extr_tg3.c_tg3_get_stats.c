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
struct tg3 {int /*<<< orphan*/  lock; struct net_device_stats net_stats_prev; int /*<<< orphan*/  hw_stats; struct net_device_stats net_stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_get_nstats (struct tg3*) ; 

__attribute__((used)) static struct net_device_stats *tg3_get_stats(struct net_device *dev)
{
	struct tg3 *tp = netdev_priv(dev);
	struct net_device_stats *stats = &tp->net_stats;

	spin_lock_bh(&tp->lock);
	if (!tp->hw_stats) {
		spin_unlock_bh(&tp->lock);
		return &tp->net_stats_prev;
	}

	tg3_get_nstats(tp);
	spin_unlock_bh(&tp->lock);

	return stats;
}