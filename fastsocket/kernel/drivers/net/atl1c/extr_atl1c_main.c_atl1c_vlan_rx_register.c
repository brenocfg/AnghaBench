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
typedef  int /*<<< orphan*/  u32 ;
struct vlan_group {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  hw; struct vlan_group* vlgrp; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AT_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_CTRL_RMV_VLAN ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  atl1c_irq_disable (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_irq_enable (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_pktdata (struct atl1c_adapter*) ; 

__attribute__((used)) static void atl1c_vlan_rx_register(struct net_device *netdev,
				   struct vlan_group *grp)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct pci_dev *pdev = adapter->pdev;
	u32 mac_ctrl_data = 0;

	if (netif_msg_pktdata(adapter))
		dev_dbg(&pdev->dev, "atl1c_vlan_rx_register\n");

	atl1c_irq_disable(adapter);

	adapter->vlgrp = grp;
	AT_READ_REG(&adapter->hw, REG_MAC_CTRL, &mac_ctrl_data);

	if (grp) {
		/* enable VLAN tag insert/strip */
		mac_ctrl_data |= MAC_CTRL_RMV_VLAN;
	} else {
		/* disable VLAN tag insert/strip */
		mac_ctrl_data &= ~MAC_CTRL_RMV_VLAN;
	}

	AT_WRITE_REG(&adapter->hw, REG_MAC_CTRL, mac_ctrl_data);
	atl1c_irq_enable(adapter);
}