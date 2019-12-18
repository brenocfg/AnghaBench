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
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  chipset_init (struct net_device*) ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 
 int /*<<< orphan*/  sja1000_netdev_ops ; 
 int /*<<< orphan*/  sja1000_probe_chip (struct net_device*) ; 

int register_sja1000dev(struct net_device *dev)
{
	if (!sja1000_probe_chip(dev))
		return -ENODEV;

	dev->flags |= IFF_ECHO;	/* we support local echo */
	dev->netdev_ops = &sja1000_netdev_ops;

	set_reset_mode(dev);
	chipset_init(dev);

	return register_candev(dev);
}