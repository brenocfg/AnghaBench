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
struct net_device {int watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ixgbevf_netdev_ops ; 
 int /*<<< orphan*/  ixgbevf_set_ethtool_ops (struct net_device*) ; 

__attribute__((used)) static void ixgbevf_assign_netdev_ops(struct net_device *dev)
{
	dev->netdev_ops = &ixgbevf_netdev_ops;
	ixgbevf_set_ethtool_ops(dev);
	dev->watchdog_timeo = 5 * HZ;
}