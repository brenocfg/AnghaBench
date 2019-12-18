#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {void* blink_led; void* led_on; void* check_mng_mode; void* set_lan_id; void* get_link_up_info; int /*<<< orphan*/  check_for_link; void* setup_physical_interface; } ;
struct e1000_mac_info {int mta_reg_count; int adaptive_ifs; int type; int has_fwsm; int arc_subsystem_valid; TYPE_4__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_11__ {scalar_t__ smb_counter; } ;
struct TYPE_12__ {TYPE_5__ e82571; } ;
struct TYPE_9__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {TYPE_6__ dev_spec; struct e1000_mac_info mac; TYPE_3__ phy; TYPE_2__* adapter; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_8__ {TYPE_1__* pdev; } ;
struct TYPE_7__ {int device; } ;

/* Variables and functions */
#define  E1000_DEV_ID_82571EB_FIBER 139 
#define  E1000_DEV_ID_82571EB_QUAD_FIBER 138 
#define  E1000_DEV_ID_82571EB_SERDES 137 
#define  E1000_DEV_ID_82571EB_SERDES_DUAL 136 
#define  E1000_DEV_ID_82571EB_SERDES_QUAD 135 
#define  E1000_DEV_ID_82572EI_FIBER 134 
#define  E1000_DEV_ID_82572EI_SERDES 133 
 int E1000_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int E1000_SWSM2_LOCK ; 
 int E1000_SWSM_SMBI ; 
 int /*<<< orphan*/  FWSM ; 
 int /*<<< orphan*/  SWSM ; 
 int /*<<< orphan*/  SWSM2 ; 
#define  e1000_82571 132 
#define  e1000_82572 131 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 int /*<<< orphan*/  e1000_check_for_serdes_link_82571 ; 
 void* e1000_check_mng_mode_82574 ; 
 void* e1000_led_on_82574 ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 void* e1000_set_lan_id_single_port ; 
 void* e1000_setup_copper_link_82571 ; 
 void* e1000_setup_fiber_serdes_link_82571 ; 
 void* e1000e_blink_led_generic ; 
 int /*<<< orphan*/  e1000e_check_for_copper_link ; 
 int /*<<< orphan*/  e1000e_check_for_fiber_link ; 
 void* e1000e_check_mng_mode_generic ; 
 void* e1000e_get_speed_and_duplex_copper ; 
 void* e1000e_get_speed_and_duplex_fiber_serdes ; 
 void* e1000e_led_on_generic ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_init_mac_params_82571(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 swsm = 0;
	u32 swsm2 = 0;
	bool force_clear_smbi = false;

	/* Set media type and media-dependent function pointers */
	switch (hw->adapter->pdev->device) {
	case E1000_DEV_ID_82571EB_FIBER:
	case E1000_DEV_ID_82572EI_FIBER:
	case E1000_DEV_ID_82571EB_QUAD_FIBER:
		hw->phy.media_type = e1000_media_type_fiber;
		mac->ops.setup_physical_interface =
		    e1000_setup_fiber_serdes_link_82571;
		mac->ops.check_for_link = e1000e_check_for_fiber_link;
		mac->ops.get_link_up_info =
		    e1000e_get_speed_and_duplex_fiber_serdes;
		break;
	case E1000_DEV_ID_82571EB_SERDES:
	case E1000_DEV_ID_82571EB_SERDES_DUAL:
	case E1000_DEV_ID_82571EB_SERDES_QUAD:
	case E1000_DEV_ID_82572EI_SERDES:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		mac->ops.setup_physical_interface =
		    e1000_setup_fiber_serdes_link_82571;
		mac->ops.check_for_link = e1000_check_for_serdes_link_82571;
		mac->ops.get_link_up_info =
		    e1000e_get_speed_and_duplex_fiber_serdes;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		mac->ops.setup_physical_interface =
		    e1000_setup_copper_link_82571;
		mac->ops.check_for_link = e1000e_check_for_copper_link;
		mac->ops.get_link_up_info = e1000e_get_speed_and_duplex_copper;
		break;
	}

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;
	/* Adaptive IFS supported */
	mac->adaptive_ifs = true;

	/* MAC-specific function pointers */
	switch (hw->mac.type) {
	case e1000_82573:
		mac->ops.set_lan_id = e1000_set_lan_id_single_port;
		mac->ops.check_mng_mode = e1000e_check_mng_mode_generic;
		mac->ops.led_on = e1000e_led_on_generic;
		mac->ops.blink_led = e1000e_blink_led_generic;

		/* FWSM register */
		mac->has_fwsm = true;
		/* ARC supported; valid only if manageability features are
		 * enabled.
		 */
		mac->arc_subsystem_valid = !!(er32(FWSM) &
					      E1000_FWSM_MODE_MASK);
		break;
	case e1000_82574:
	case e1000_82583:
		mac->ops.set_lan_id = e1000_set_lan_id_single_port;
		mac->ops.check_mng_mode = e1000_check_mng_mode_82574;
		mac->ops.led_on = e1000_led_on_82574;
		break;
	default:
		mac->ops.check_mng_mode = e1000e_check_mng_mode_generic;
		mac->ops.led_on = e1000e_led_on_generic;
		mac->ops.blink_led = e1000e_blink_led_generic;

		/* FWSM register */
		mac->has_fwsm = true;
		break;
	}

	/* Ensure that the inter-port SWSM.SMBI lock bit is clear before
	 * first NVM or PHY access. This should be done for single-port
	 * devices, and for one port only on dual-port devices so that
	 * for those devices we can still use the SMBI lock to synchronize
	 * inter-port accesses to the PHY & NVM.
	 */
	switch (hw->mac.type) {
	case e1000_82571:
	case e1000_82572:
		swsm2 = er32(SWSM2);

		if (!(swsm2 & E1000_SWSM2_LOCK)) {
			/* Only do this for the first interface on this card */
			ew32(SWSM2, swsm2 | E1000_SWSM2_LOCK);
			force_clear_smbi = true;
		} else {
			force_clear_smbi = false;
		}
		break;
	default:
		force_clear_smbi = true;
		break;
	}

	if (force_clear_smbi) {
		/* Make sure SWSM.SMBI is clear */
		swsm = er32(SWSM);
		if (swsm & E1000_SWSM_SMBI) {
			/* This bit should not be set on a first interface, and
			 * indicates that the bootagent or EFI code has
			 * improperly left this bit enabled
			 */
			e_dbg("Please update your 82571 Bootagent\n");
		}
		ew32(SWSM, swsm & ~E1000_SWSM_SMBI);
	}

	/* Initialize device specific counter of SMBI acquisition timeouts. */
	hw->dev_spec.e82571.smb_counter = 0;

	return 0;
}