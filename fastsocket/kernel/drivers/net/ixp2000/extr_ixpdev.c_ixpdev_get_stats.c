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
struct ixpdev_priv {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct ixpdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pm3386_get_stats (int /*<<< orphan*/ ,struct net_device_stats*) ; 

__attribute__((used)) static struct net_device_stats *ixpdev_get_stats(struct net_device *dev)
{
	struct ixpdev_priv *ip = netdev_priv(dev);

	pm3386_get_stats(ip->channel, &(dev->stats));

	return &(dev->stats);
}