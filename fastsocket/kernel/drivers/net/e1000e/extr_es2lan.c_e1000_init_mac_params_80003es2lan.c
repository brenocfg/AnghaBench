#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* set_lan_id ) (struct e1000_hw*) ;int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  check_for_link; } ;
struct e1000_mac_info {int mta_reg_count; int has_fwsm; int arc_subsystem_valid; int adaptive_ifs; TYPE_4__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {struct e1000_mac_info mac; TYPE_3__ phy; TYPE_2__* adapter; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
#define  E1000_DEV_ID_80003ES2LAN_SERDES_DPT 128 
 int E1000_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int /*<<< orphan*/  FWSM ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_setup_copper_link_80003es2lan ; 
 int /*<<< orphan*/  e1000e_check_for_copper_link ; 
 int /*<<< orphan*/  e1000e_check_for_serdes_link ; 
 int /*<<< orphan*/  e1000e_setup_fiber_serdes_link ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_mac_params_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	/* Set media type and media-dependent function pointers */
	switch (hw->adapter->pdev->device) {
	case E1000_DEV_ID_80003ES2LAN_SERDES_DPT:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		mac->ops.check_for_link = e1000e_check_for_serdes_link;
		mac->ops.setup_physical_interface =
		    e1000e_setup_fiber_serdes_link;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		mac->ops.check_for_link = e1000e_check_for_copper_link;
		mac->ops.setup_physical_interface =
		    e1000_setup_copper_link_80003es2lan;
		break;
	}

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;
	/* FWSM register */
	mac->has_fwsm = true;
	/* ARC supported; valid only if manageability features are enabled. */
	mac->arc_subsystem_valid = !!(er32(FWSM) & E1000_FWSM_MODE_MASK);
	/* Adaptive IFS not supported */
	mac->adaptive_ifs = false;

	/* set lan id for port to determine which phy lock to use */
	hw->mac.ops.set_lan_id(hw);

	return 0;
}