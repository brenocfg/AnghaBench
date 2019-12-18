#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  revision; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct e1000_hw {int mac_type; int phy_init_script; int wait_autoneg_complete; int tbi_compatibility_en; int adaptive_ifs; scalar_t__ media_type; int disable_polarity_correction; int /*<<< orphan*/  master_slave; int /*<<< orphan*/  mdix; int /*<<< orphan*/  min_frame_size; scalar_t__ max_frame_size; int /*<<< orphan*/  pci_cmd_word; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  subsystem_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct e1000_adapter {TYPE_1__* netdev; struct pci_dev* pdev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_ALL_MODES ; 
 int /*<<< orphan*/  E1000_MASTER_SLAVE ; 
 int EIO ; 
 scalar_t__ ENET_HEADER_SIZE ; 
 scalar_t__ ETHERNET_FCS_SIZE ; 
 int /*<<< orphan*/  MINIMUM_ETHERNET_FRAME_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
#define  e1000_82541 131 
#define  e1000_82541_rev_2 130 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 int /*<<< orphan*/  e1000_get_bus_info (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_set_mac_type (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_set_media_type (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int e1000_init_hw_struct(struct e1000_adapter *adapter,
				struct e1000_hw *hw)
{
	struct pci_dev *pdev = adapter->pdev;

	/* PCI config space info */
	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_id = pdev->subsystem_device;
	hw->revision_id = pdev->revision;

	pci_read_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	hw->max_frame_size = adapter->netdev->mtu +
			     ENET_HEADER_SIZE + ETHERNET_FCS_SIZE;
	hw->min_frame_size = MINIMUM_ETHERNET_FRAME_SIZE;

	/* identify the MAC */
	if (e1000_set_mac_type(hw)) {
		e_err(probe, "Unknown MAC Type\n");
		return -EIO;
	}

	switch (hw->mac_type) {
	default:
		break;
	case e1000_82541:
	case e1000_82547:
	case e1000_82541_rev_2:
	case e1000_82547_rev_2:
		hw->phy_init_script = 1;
		break;
	}

	e1000_set_media_type(hw);
	e1000_get_bus_info(hw);

	hw->wait_autoneg_complete = false;
	hw->tbi_compatibility_en = true;
	hw->adaptive_ifs = true;

	/* Copper options */

	if (hw->media_type == e1000_media_type_copper) {
		hw->mdix = AUTO_ALL_MODES;
		hw->disable_polarity_correction = false;
		hw->master_slave = E1000_MASTER_SLAVE;
	}

	return 0;
}