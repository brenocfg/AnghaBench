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
struct pci_dev {int device; } ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/  max_hw_frame_size; struct e1000_hw hw; struct pci_dev* pdev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_JUMBO ; 
 int E1000_DEV_ID_82571EB_COPPER ; 
 int E1000_DEV_ID_82571EB_FIBER ; 
#define  E1000_DEV_ID_82571EB_QUAD_COPPER 133 
#define  E1000_DEV_ID_82571EB_QUAD_COPPER_LP 132 
#define  E1000_DEV_ID_82571EB_QUAD_FIBER 131 
 int E1000_DEV_ID_82571EB_SERDES ; 
 int E1000_DEV_ID_82571EB_SERDES_QUAD ; 
#define  E1000_DEV_ID_82571PT_QUAD_COPPER 130 
 int E1000_DEV_ID_82573L ; 
 int E1000_STATUS_FUNC_1 ; 
 int FLAG_HAS_JUMBO_FRAMES ; 
 int FLAG_HAS_WOL ; 
 int FLAG_IS_QUAD_PORT ; 
 int FLAG_IS_QUAD_PORT_A ; 
 int /*<<< orphan*/  STATUS ; 
#define  e1000_82571 129 
#define  e1000_82573 128 
 scalar_t__ e1000_init_mac_params_82571 (struct e1000_hw*) ; 
 scalar_t__ e1000_init_nvm_params_82571 (struct e1000_hw*) ; 
 scalar_t__ e1000_init_phy_params_82571 (struct e1000_hw*) ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_get_variants_82571(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	static int global_quad_port_a;	/* global port a indication */
	struct pci_dev *pdev = adapter->pdev;
	int is_port_b = er32(STATUS) & E1000_STATUS_FUNC_1;
	s32 rc;

	rc = e1000_init_mac_params_82571(hw);
	if (rc)
		return rc;

	rc = e1000_init_nvm_params_82571(hw);
	if (rc)
		return rc;

	rc = e1000_init_phy_params_82571(hw);
	if (rc)
		return rc;

	/* tag quad port adapters first, it's used below */
	switch (pdev->device) {
	case E1000_DEV_ID_82571EB_QUAD_COPPER:
	case E1000_DEV_ID_82571EB_QUAD_FIBER:
	case E1000_DEV_ID_82571EB_QUAD_COPPER_LP:
	case E1000_DEV_ID_82571PT_QUAD_COPPER:
		adapter->flags |= FLAG_IS_QUAD_PORT;
		/* mark the first port */
		if (global_quad_port_a == 0)
			adapter->flags |= FLAG_IS_QUAD_PORT_A;
		/* Reset for multiple quad port adapters */
		global_quad_port_a++;
		if (global_quad_port_a == 4)
			global_quad_port_a = 0;
		break;
	default:
		break;
	}

	switch (adapter->hw.mac.type) {
	case e1000_82571:
		/* these dual ports don't have WoL on port B at all */
		if (((pdev->device == E1000_DEV_ID_82571EB_FIBER) ||
		     (pdev->device == E1000_DEV_ID_82571EB_SERDES) ||
		     (pdev->device == E1000_DEV_ID_82571EB_COPPER)) &&
		    (is_port_b))
			adapter->flags &= ~FLAG_HAS_WOL;
		/* quad ports only support WoL on port A */
		if (adapter->flags & FLAG_IS_QUAD_PORT &&
		    (!(adapter->flags & FLAG_IS_QUAD_PORT_A)))
			adapter->flags &= ~FLAG_HAS_WOL;
		/* Does not support WoL on any port */
		if (pdev->device == E1000_DEV_ID_82571EB_SERDES_QUAD)
			adapter->flags &= ~FLAG_HAS_WOL;
		break;
	case e1000_82573:
		if (pdev->device == E1000_DEV_ID_82573L) {
			adapter->flags |= FLAG_HAS_JUMBO_FRAMES;
			adapter->max_hw_frame_size = DEFAULT_JUMBO;
		}
		break;
	default:
		break;
	}

	return 0;
}