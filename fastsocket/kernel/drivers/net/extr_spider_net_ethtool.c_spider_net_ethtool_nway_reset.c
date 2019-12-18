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

/* Variables and functions */
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spider_net_open (struct net_device*) ; 
 int /*<<< orphan*/  spider_net_stop (struct net_device*) ; 

__attribute__((used)) static int
spider_net_ethtool_nway_reset(struct net_device *netdev)
{
	if (netif_running(netdev)) {
		spider_net_stop(netdev);
		spider_net_open(netdev);
	}
	return 0;
}