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
struct net_device_ops {int /*<<< orphan*/  (* ndo_change_rx_flags ) (struct net_device*,int) ;} ;
struct net_device {int flags; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int) ; 

__attribute__((used)) static void dev_change_rx_flags(struct net_device *dev, int flags)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	if ((dev->flags & IFF_UP) && ops->ndo_change_rx_flags)
		ops->ndo_change_rx_flags(dev, flags);
}