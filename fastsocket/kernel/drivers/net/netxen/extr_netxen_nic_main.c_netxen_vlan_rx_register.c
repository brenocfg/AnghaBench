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
struct netxen_adapter {struct vlan_group* vlgrp; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netxen_vlan_rx_register(struct net_device *netdev,
				struct vlan_group *grp)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);
	adapter->vlgrp = grp;
}