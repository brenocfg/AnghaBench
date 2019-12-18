#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_lan_id ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {TYPE_1__ ops; } ;
struct e1000_bus_info {int width; } ;
struct e1000_hw {struct e1000_adapter* adapter; struct e1000_bus_info bus; struct e1000_mac_info mac; } ;
struct e1000_adapter {TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum e1000_bus_width { ____Placeholder_e1000_bus_width } e1000_bus_width ;
struct TYPE_4__ {int pcie_cap; } ;

/* Variables and functions */
 int PCIE_LINK_STATUS ; 
 int PCIE_LINK_WIDTH_MASK ; 
 int PCIE_LINK_WIDTH_SHIFT ; 
 int e1000_bus_width_unknown ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

s32 e1000e_get_bus_info_pcie(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_bus_info *bus = &hw->bus;
	struct e1000_adapter *adapter = hw->adapter;
	u16 pcie_link_status, cap_offset;

	cap_offset = adapter->pdev->pcie_cap;
	if (!cap_offset) {
		bus->width = e1000_bus_width_unknown;
	} else {
		pci_read_config_word(adapter->pdev,
				     cap_offset + PCIE_LINK_STATUS,
				     &pcie_link_status);
		bus->width = (enum e1000_bus_width)((pcie_link_status &
						     PCIE_LINK_WIDTH_MASK) >>
						    PCIE_LINK_WIDTH_SHIFT);
	}

	mac->ops.set_lan_id(hw);

	return 0;
}