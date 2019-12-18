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
struct ql_adapter {struct vlan_group* vlgrp; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_RCV_CFG ; 
 int NIC_RCV_CFG_VLAN_MASK ; 
 int NIC_RCV_CFG_VLAN_MATCH_AND_NON ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qlge_vlan_rx_register(struct net_device *ndev, struct vlan_group *grp)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	qdev->vlgrp = grp;
	if (grp) {
		ql_write32(qdev, NIC_RCV_CFG, NIC_RCV_CFG_VLAN_MASK |
			   NIC_RCV_CFG_VLAN_MATCH_AND_NON);
	} else {
		ql_write32(qdev, NIC_RCV_CFG, NIC_RCV_CFG_VLAN_MASK);
	}
}