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
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skge_down (struct net_device*) ; 
 int skge_up (struct net_device*) ; 

__attribute__((used)) static int skge_change_mtu(struct net_device *dev, int new_mtu)
{
	int err;

	if (new_mtu < ETH_ZLEN || new_mtu > ETH_JUMBO_MTU)
		return -EINVAL;

	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		return 0;
	}

	skge_down(dev);

	dev->mtu = new_mtu;

	err = skge_up(dev);
	if (err)
		dev_close(dev);

	return err;
}