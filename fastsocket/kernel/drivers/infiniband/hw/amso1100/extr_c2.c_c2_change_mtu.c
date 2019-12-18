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

/* Variables and functions */
 int EINVAL ; 
 int ETH_JUMBO_MTU ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  c2_down (struct net_device*) ; 
 int /*<<< orphan*/  c2_up (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int c2_change_mtu(struct net_device *netdev, int new_mtu)
{
	int ret = 0;

	if (new_mtu < ETH_ZLEN || new_mtu > ETH_JUMBO_MTU)
		return -EINVAL;

	netdev->mtu = new_mtu;

	if (netif_running(netdev)) {
		c2_down(netdev);

		c2_up(netdev);
	}

	return ret;
}