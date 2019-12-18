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
struct vlan_group {int dummy; } ;
struct net_device {int priv_flags; struct net_device* master; } ;

/* Variables and functions */
 int IFF_BONDING ; 
 struct vlan_group* __vlan_find_group (struct net_device*) ; 
 struct net_device* vlan_group_get_device (struct vlan_group*,int) ; 

__attribute__((used)) static int ignore_slave_event(struct net_device *dev, int i)
{
	struct vlan_group *sgrp, *mgrp;
	struct net_device *svdev, *mvdev;

	/* process if this isn't a slave */
	if (!dev->master)
		return 0;

	/* This is just a check for bonding */
	if (!(dev->master->priv_flags & IFF_BONDING))
		return 0;

	sgrp = __vlan_find_group(dev);
	mgrp = __vlan_find_group(dev->master);

	/* process if either the slave or master doesn't have a vlan group */
	if (!sgrp || !mgrp)
		return 0;

	svdev = vlan_group_get_device(sgrp, i);
	mvdev = vlan_group_get_device(mgrp, i);

	/* process If a vlan isn't found on either the slave or master */
	if (!svdev || !mvdev)
		return 0;

	/*
	 * If, and only if, we have the same vlan device attached to both
	 * the slave and the master device, then we know for certain that
	 * this event is coming from a slave, and that the vlan is actually
	 * attached to the master.  In this case, vlan_device_event should
	 * ignore the event process and not transfer the operstate, because
	 * the bonds operstate won't actually change, it will just fail over
	 * to another slave
	 */
	if (svdev == mvdev)
		return 1;

	return 0;
}