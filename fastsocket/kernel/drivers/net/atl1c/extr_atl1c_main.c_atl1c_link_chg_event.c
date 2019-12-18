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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct atl1c_adapter {int /*<<< orphan*/  common_task; int /*<<< orphan*/  work_event; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  hw; struct pci_dev* pdev; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL1C_WORK_EVENT_LINK_CHANGE ; 
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  atl1c_driver_name ; 
 int /*<<< orphan*/  atl1c_read_phy_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl1c_link_chg_event(struct atl1c_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev    *pdev   = adapter->pdev;
	u16 phy_data;
	u16 link_up;

	spin_lock(&adapter->mdio_lock);
	atl1c_read_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	atl1c_read_phy_reg(&adapter->hw, MII_BMSR, &phy_data);
	spin_unlock(&adapter->mdio_lock);
	link_up = phy_data & BMSR_LSTATUS;
	/* notify upper layer link down ASAP */
	if (!link_up) {
		if (netif_carrier_ok(netdev)) {
			/* old link state: Up */
			netif_carrier_off(netdev);
			if (netif_msg_link(adapter))
				dev_info(&pdev->dev,
					"%s: %s NIC Link is Down\n",
					atl1c_driver_name, netdev->name);
			adapter->link_speed = SPEED_0;
		}
	}

	set_bit(ATL1C_WORK_EVENT_LINK_CHANGE, &adapter->work_event);
	schedule_work(&adapter->common_task);
}