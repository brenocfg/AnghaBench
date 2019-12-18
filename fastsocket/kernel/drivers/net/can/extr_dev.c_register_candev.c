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
struct net_device {int /*<<< orphan*/ * rtnl_link_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_link_ops ; 
 int register_netdev (struct net_device*) ; 

int register_candev(struct net_device *dev)
{
	dev->rtnl_link_ops = &can_link_ops;
	return register_netdev(dev);
}