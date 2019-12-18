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
typedef  scalar_t__ u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct atl1e_hw {int dummy; } ;
struct atl1e_adapter {scalar_t__ link_speed; scalar_t__ link_duplex; struct pci_dev* pdev; struct net_device* netdev; struct atl1e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BMSR_LSTATUS ; 
 scalar_t__ FULL_DUPLEX ; 
 int /*<<< orphan*/  MAC_CTRL_RX_EN ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 scalar_t__ SPEED_0 ; 
 int /*<<< orphan*/  atl1e_driver_name ; 
 int atl1e_get_speed_and_duplex (struct atl1e_hw*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  atl1e_read_phy_reg (struct atl1e_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  atl1e_setup_mac_ctrl (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1e_check_link(struct atl1e_adapter *adapter)
{
	struct atl1e_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev    *pdev   = adapter->pdev;
	int err = 0;
	u16 speed, duplex, phy_data;

	/* MII_BMSR must read twise */
	atl1e_read_phy_reg(hw, MII_BMSR, &phy_data);
	atl1e_read_phy_reg(hw, MII_BMSR, &phy_data);
	if ((phy_data & BMSR_LSTATUS) == 0) {
		/* link down */
		if (netif_carrier_ok(netdev)) { /* old link state: Up */
			u32 value;
			/* disable rx */
			value = AT_READ_REG(hw, REG_MAC_CTRL);
			value &= ~MAC_CTRL_RX_EN;
			AT_WRITE_REG(hw, REG_MAC_CTRL, value);
			adapter->link_speed = SPEED_0;
			netif_carrier_off(netdev);
			netif_stop_queue(netdev);
		}
	} else {
		/* Link Up */
		err = atl1e_get_speed_and_duplex(hw, &speed, &duplex);
		if (unlikely(err))
			return err;

		/* link result is our setting */
		if (adapter->link_speed != speed ||
		    adapter->link_duplex != duplex) {
			adapter->link_speed  = speed;
			adapter->link_duplex = duplex;
			atl1e_setup_mac_ctrl(adapter);
			dev_info(&pdev->dev,
				"%s: %s NIC Link is Up<%d Mbps %s>\n",
				atl1e_driver_name, netdev->name,
				adapter->link_speed,
				adapter->link_duplex == FULL_DUPLEX ?
				"Full Duplex" : "Half Duplex");
		}

		if (!netif_carrier_ok(netdev)) {
			/* Link down -> Up */
			netif_carrier_on(netdev);
			netif_wake_queue(netdev);
		}
	}
	return 0;
}