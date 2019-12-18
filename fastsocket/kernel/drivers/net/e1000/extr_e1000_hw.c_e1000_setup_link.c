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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {int fc; scalar_t__ mac_type; int report_tx_early; int original_fc; scalar_t__ media_type; int fc_pause_time; int fc_low_water; int fc_high_water; scalar_t__ fc_send_xon; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_EXT ; 
 scalar_t__ E1000_ERR_EEPROM ; 
 int E1000_FCRTL_XONE ; 
 int E1000_FC_DEFAULT ; 
 int E1000_FC_FULL ; 
 int E1000_FC_NONE ; 
 int E1000_FC_RX_PAUSE ; 
 int E1000_FC_TX_PAUSE ; 
 int /*<<< orphan*/  EEPROM_INIT_CONTROL2_REG ; 
 int EEPROM_WORD0F_ASM_DIR ; 
 int EEPROM_WORD0F_PAUSE_MASK ; 
 int EEPROM_WORD0F_SWPDIO_EXT ; 
 int /*<<< orphan*/  FCAH ; 
 int /*<<< orphan*/  FCAL ; 
 int /*<<< orphan*/  FCRTH ; 
 int /*<<< orphan*/  FCRTL ; 
 int /*<<< orphan*/  FCT ; 
 int /*<<< orphan*/  FCTTV ; 
 int FLOW_CONTROL_ADDRESS_HIGH ; 
 int FLOW_CONTROL_ADDRESS_LOW ; 
 int FLOW_CONTROL_TYPE ; 
 int SWDPIO__EXT_SHIFT ; 
 scalar_t__ e1000_82542_rev2_0 ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_read_eeprom (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ e1000_setup_copper_link (struct e1000_hw*) ; 
 scalar_t__ e1000_setup_fiber_serdes_link (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

s32 e1000_setup_link(struct e1000_hw *hw)
{
	u32 ctrl_ext;
	s32 ret_val;
	u16 eeprom_data;

	e_dbg("e1000_setup_link");

	/* Read and store word 0x0F of the EEPROM. This word contains bits
	 * that determine the hardware's default PAUSE (flow control) mode,
	 * a bit that determines whether the HW defaults to enabling or
	 * disabling auto-negotiation, and the direction of the
	 * SW defined pins. If there is no SW over-ride of the flow
	 * control setting, then the variable hw->fc will
	 * be initialized based on a value in the EEPROM.
	 */
	if (hw->fc == E1000_FC_DEFAULT) {
		ret_val = e1000_read_eeprom(hw, EEPROM_INIT_CONTROL2_REG,
					    1, &eeprom_data);
		if (ret_val) {
			e_dbg("EEPROM Read Error\n");
			return -E1000_ERR_EEPROM;
		}
		if ((eeprom_data & EEPROM_WORD0F_PAUSE_MASK) == 0)
			hw->fc = E1000_FC_NONE;
		else if ((eeprom_data & EEPROM_WORD0F_PAUSE_MASK) ==
			 EEPROM_WORD0F_ASM_DIR)
			hw->fc = E1000_FC_TX_PAUSE;
		else
			hw->fc = E1000_FC_FULL;
	}

	/* We want to save off the original Flow Control configuration just
	 * in case we get disconnected and then reconnected into a different
	 * hub or switch with different Flow Control capabilities.
	 */
	if (hw->mac_type == e1000_82542_rev2_0)
		hw->fc &= (~E1000_FC_TX_PAUSE);

	if ((hw->mac_type < e1000_82543) && (hw->report_tx_early == 1))
		hw->fc &= (~E1000_FC_RX_PAUSE);

	hw->original_fc = hw->fc;

	e_dbg("After fix-ups FlowControl is now = %x\n", hw->fc);

	/* Take the 4 bits from EEPROM word 0x0F that determine the initial
	 * polarity value for the SW controlled pins, and setup the
	 * Extended Device Control reg with that info.
	 * This is needed because one of the SW controlled pins is used for
	 * signal detection.  So this should be done before e1000_setup_pcs_link()
	 * or e1000_phy_setup() is called.
	 */
	if (hw->mac_type == e1000_82543) {
		ret_val = e1000_read_eeprom(hw, EEPROM_INIT_CONTROL2_REG,
					    1, &eeprom_data);
		if (ret_val) {
			e_dbg("EEPROM Read Error\n");
			return -E1000_ERR_EEPROM;
		}
		ctrl_ext = ((eeprom_data & EEPROM_WORD0F_SWPDIO_EXT) <<
			    SWDPIO__EXT_SHIFT);
		ew32(CTRL_EXT, ctrl_ext);
	}

	/* Call the necessary subroutine to configure the link. */
	ret_val = (hw->media_type == e1000_media_type_copper) ?
	    e1000_setup_copper_link(hw) : e1000_setup_fiber_serdes_link(hw);

	/* Initialize the flow control address, type, and PAUSE timer
	 * registers to their default values.  This is done even if flow
	 * control is disabled, because it does not hurt anything to
	 * initialize these registers.
	 */
	e_dbg("Initializing the Flow Control address, type and timer regs\n");

	ew32(FCT, FLOW_CONTROL_TYPE);
	ew32(FCAH, FLOW_CONTROL_ADDRESS_HIGH);
	ew32(FCAL, FLOW_CONTROL_ADDRESS_LOW);

	ew32(FCTTV, hw->fc_pause_time);

	/* Set the flow control receive threshold registers.  Normally,
	 * these registers will be set to a default threshold that may be
	 * adjusted later by the driver's runtime code.  However, if the
	 * ability to transmit pause frames in not enabled, then these
	 * registers will be set to 0.
	 */
	if (!(hw->fc & E1000_FC_TX_PAUSE)) {
		ew32(FCRTL, 0);
		ew32(FCRTH, 0);
	} else {
		/* We need to set up the Receive Threshold high and low water marks
		 * as well as (optionally) enabling the transmission of XON frames.
		 */
		if (hw->fc_send_xon) {
			ew32(FCRTL, (hw->fc_low_water | E1000_FCRTL_XONE));
			ew32(FCRTH, hw->fc_high_water);
		} else {
			ew32(FCRTL, hw->fc_low_water);
			ew32(FCRTH, hw->fc_high_water);
		}
	}
	return ret_val;
}