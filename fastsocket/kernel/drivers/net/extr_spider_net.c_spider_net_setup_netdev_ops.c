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
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  spider_net_ethtool_ops ; 
 int /*<<< orphan*/  spider_net_ops ; 

__attribute__((used)) static void
spider_net_setup_netdev_ops(struct net_device *netdev)
{
	netdev->netdev_ops = &spider_net_ops;
	netdev->watchdog_timeo = SPIDER_NET_WATCHDOG_TIMEOUT;
	/* ethtool ops */
	netdev->ethtool_ops = &spider_net_ethtool_ops;
}