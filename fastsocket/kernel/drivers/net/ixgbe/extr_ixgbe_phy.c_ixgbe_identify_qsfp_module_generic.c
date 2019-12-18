#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_7__ {scalar_t__ (* read_i2c_eeprom ) (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_10__ {int sfp_type; scalar_t__ type; int sfp_setup_needed; int multispeed_fiber; scalar_t__ id; TYPE_2__ ops; } ;
struct TYPE_8__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* get_device_caps ) (struct ixgbe_hw*,int*) ;int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_9__ {TYPE_3__ ops; } ;
struct TYPE_6__ {scalar_t__ lan_id; } ;
struct ixgbe_hw {int allow_unsupported_sfp; TYPE_5__ phy; TYPE_4__ mac; TYPE_1__ bus; struct ixgbe_adapter* back; } ;
struct ixgbe_adapter {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum ixgbe_sfp_type { ____Placeholder_ixgbe_sfp_type } ixgbe_sfp_type ;

/* Variables and functions */
 int IXGBE_DEVICE_CAPS_ALLOW_ANY_SFP ; 
 scalar_t__ IXGBE_ERR_PHY_ADDR_INVALID ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_PRESENT ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 scalar_t__ IXGBE_SFF_10GBASELR_CAPABLE ; 
 scalar_t__ IXGBE_SFF_10GBASESR_CAPABLE ; 
 scalar_t__ IXGBE_SFF_1GBASELX_CAPABLE ; 
 scalar_t__ IXGBE_SFF_1GBASESX_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_IDENTIFIER ; 
 scalar_t__ IXGBE_SFF_IDENTIFIER_QSFP_PLUS ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_10GBE_COMP ; 
 scalar_t__ IXGBE_SFF_QSFP_DA_ACTIVE_CABLE ; 
 scalar_t__ IXGBE_SFF_QSFP_DA_PASSIVE_CABLE ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_VENDOR_OUI_BYTE0 ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_VENDOR_OUI_BYTE1 ; 
 int /*<<< orphan*/  IXGBE_SFF_QSFP_VENDOR_OUI_BYTE2 ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT ; 
 scalar_t__ IXGBE_SFF_VENDOR_OUI_INTEL ; 
 int /*<<< orphan*/  e_warn (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_media_type_fiber_qsfp ; 
 scalar_t__ ixgbe_phy_qsfp_active_unknown ; 
 scalar_t__ ixgbe_phy_qsfp_intel ; 
 scalar_t__ ixgbe_phy_qsfp_passive_unknown ; 
 scalar_t__ ixgbe_phy_qsfp_unknown ; 
 void* ixgbe_phy_sfp_unsupported ; 
 scalar_t__ ixgbe_phy_unknown ; 
 int ixgbe_sfp_type_da_act_lmt_core0 ; 
 int ixgbe_sfp_type_da_act_lmt_core1 ; 
 int ixgbe_sfp_type_da_cu_core0 ; 
 int ixgbe_sfp_type_da_cu_core1 ; 
 void* ixgbe_sfp_type_not_present ; 
 int ixgbe_sfp_type_srlr_core0 ; 
 int ixgbe_sfp_type_srlr_core1 ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int*) ; 

s32 ixgbe_identify_qsfp_module_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_adapter *adapter = hw->back;
	s32 status = IXGBE_ERR_PHY_ADDR_INVALID;
	u32 vendor_oui = 0;
	enum ixgbe_sfp_type stored_sfp_type = hw->phy.sfp_type;
	u8 identifier = 0;
	u8 comp_codes_1g = 0;
	u8 comp_codes_10g = 0;
	u8 oui_bytes[3] = {0, 0, 0};
	u16 enforce_sfp = 0;

	if (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_fiber_qsfp) {
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		status = IXGBE_ERR_SFP_NOT_PRESENT;
		goto out;
	}

	status = hw->phy.ops.read_i2c_eeprom(hw, IXGBE_SFF_IDENTIFIER,
					     &identifier);

	if (status != 0)
		goto err_read_i2c_eeprom;

	if (identifier != IXGBE_SFF_IDENTIFIER_QSFP_PLUS) {
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		status = IXGBE_ERR_SFP_NOT_SUPPORTED;
		goto out;
	}

	hw->phy.id = identifier;

	/* LAN ID is needed for sfp_type determination */
	hw->mac.ops.set_lan_id(hw);

	status = hw->phy.ops.read_i2c_eeprom(hw, IXGBE_SFF_QSFP_10GBE_COMP,
					     &comp_codes_10g);

	if (status != 0)
		goto err_read_i2c_eeprom;

	if (comp_codes_10g & IXGBE_SFF_QSFP_DA_PASSIVE_CABLE) {
		hw->phy.type = ixgbe_phy_qsfp_passive_unknown;
		if (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_core0;
		else
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_core1;
	} else if (comp_codes_10g & IXGBE_SFF_QSFP_DA_ACTIVE_CABLE) {
		hw->phy.type = ixgbe_phy_qsfp_active_unknown;
		if (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_da_act_lmt_core0;
		else
			hw->phy.sfp_type = ixgbe_sfp_type_da_act_lmt_core1;
	} else if (comp_codes_10g & (IXGBE_SFF_10GBASESR_CAPABLE |
				     IXGBE_SFF_10GBASELR_CAPABLE)) {
		if (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_srlr_core0;
		else
			hw->phy.sfp_type = ixgbe_sfp_type_srlr_core1;
	} else {
		/* unsupported module type */
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		status = IXGBE_ERR_SFP_NOT_SUPPORTED;
		goto out;
	}

	if (hw->phy.sfp_type != stored_sfp_type)
		hw->phy.sfp_setup_needed = true;

	/* Determine if the QSFP+ PHY is dual speed or not. */
	hw->phy.multispeed_fiber = false;
	if (((comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)) ||
	    ((comp_codes_1g & IXGBE_SFF_1GBASELX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)))
		hw->phy.multispeed_fiber = true;

	/* Determine PHY vendor for optical modules */
	if (comp_codes_10g & (IXGBE_SFF_10GBASESR_CAPABLE |
			      IXGBE_SFF_10GBASELR_CAPABLE)) {
		status = hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE0,
					&oui_bytes[0]);

		if (status != 0)
			goto err_read_i2c_eeprom;

		status = hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE1,
					&oui_bytes[1]);

		if (status != 0)
			goto err_read_i2c_eeprom;

		status = hw->phy.ops.read_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE2,
					&oui_bytes[2]);

		if (status != 0)
			goto err_read_i2c_eeprom;

		vendor_oui =
			((oui_bytes[0] << IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT) |
			 (oui_bytes[1] << IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT) |
			 (oui_bytes[2] << IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT));

		if (vendor_oui == IXGBE_SFF_VENDOR_OUI_INTEL)
			hw->phy.type = ixgbe_phy_qsfp_intel;
		else
			hw->phy.type = ixgbe_phy_qsfp_unknown;

		hw->mac.ops.get_device_caps(hw, &enforce_sfp);
		if (!(enforce_sfp & IXGBE_DEVICE_CAPS_ALLOW_ANY_SFP)) {
			/* Make sure we're a supported PHY type */
			if (hw->phy.type == ixgbe_phy_qsfp_intel) {
				status = 0;
			} else {
				if (hw->allow_unsupported_sfp == true) {
					e_warn(hw, "WARNING: Intel (R) Network Connections are quality tested using Intel (R) Ethernet Optics. Using untested modules is not supported and may cause unstable operation or damage to the module or the adapter. Intel Corporation is not responsible for any harm caused by using untested modules.\n");
					status = 0;
				} else {
					hw_dbg(hw,
					       "QSFP module not supported\n");
					hw->phy.type =
						ixgbe_phy_sfp_unsupported;
					status = IXGBE_ERR_SFP_NOT_SUPPORTED;
				}
			}
		} else {
			status = 0;
		}
	}

out:
	return status;

err_read_i2c_eeprom:
	hw->phy.sfp_type = ixgbe_sfp_type_not_present;
	hw->phy.id = 0;
	hw->phy.type = ixgbe_phy_unknown;

	return IXGBE_ERR_SFP_NOT_PRESENT;
}