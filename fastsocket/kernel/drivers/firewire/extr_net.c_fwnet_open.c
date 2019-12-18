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
struct fwnet_device {scalar_t__ broadcast_state; } ;

/* Variables and functions */
 scalar_t__ FWNET_BROADCAST_ERROR ; 
 int fwnet_broadcast_start (struct fwnet_device*) ; 
 struct fwnet_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static int fwnet_open(struct net_device *net)
{
	struct fwnet_device *dev = netdev_priv(net);
	int ret;

	if (dev->broadcast_state == FWNET_BROADCAST_ERROR) {
		ret = fwnet_broadcast_start(dev);
		if (ret)
			return ret;
	}
	netif_start_queue(net);

	return 0;
}