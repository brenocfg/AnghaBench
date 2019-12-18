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
 int EBUSY ; 
 int compute_hw_mtu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bcm_enet_change_mtu(struct net_device *dev, int new_mtu)
{
	int ret;

	if (netif_running(dev))
		return -EBUSY;

	ret = compute_hw_mtu(netdev_priv(dev), new_mtu);
	if (ret)
		return ret;
	dev->mtu = new_mtu;
	return 0;
}