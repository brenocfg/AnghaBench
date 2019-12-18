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
typedef  int u16 ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; struct ixgbe_adapter* back; } ;
struct ixgbe_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int IXGBE_MAX_MSIX_VECTORS_82598 ; 
 int IXGBE_MAX_MSIX_VECTORS_82599 ; 
 int IXGBE_PCIE_MSIX_82598_CAPS ; 
 int IXGBE_PCIE_MSIX_82599_CAPS ; 
 int IXGBE_PCIE_MSIX_TBL_SZ_MASK ; 
#define  ixgbe_mac_82598EB 130 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 

u16 ixgbe_get_pcie_msix_count_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_adapter *adapter = hw->back;
	u16 msix_count = 1;
	u16 max_msix_count;
	u16 pcie_offset;

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		pcie_offset = IXGBE_PCIE_MSIX_82598_CAPS;
		max_msix_count = IXGBE_MAX_MSIX_VECTORS_82598;
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		pcie_offset = IXGBE_PCIE_MSIX_82599_CAPS;
		max_msix_count = IXGBE_MAX_MSIX_VECTORS_82599;
		break;
	default:
		return msix_count;
	}

	pci_read_config_word(adapter->pdev, pcie_offset, &msix_count);
	msix_count &= IXGBE_PCIE_MSIX_TBL_SZ_MASK;

	/* MSI-X count is zero-based in HW */
	msix_count++;

	if (msix_count > max_msix_count)
		msix_count = max_msix_count;

	return msix_count;
}