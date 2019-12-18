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
struct e1000_hw {scalar_t__ mac_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_SDP4_DATA ; 
 int E1000_CTRL_EXT_SDP4_DIR ; 
 int E1000_CTRL_PHY_RST ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int IGP_ACTIVITY_LED_ENABLE ; 
 int IGP_ACTIVITY_LED_MASK ; 
 int IGP_LED3_MODE ; 
 int /*<<< orphan*/  LEDCTL ; 
 scalar_t__ e1000_82541 ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_82547 ; 
 int /*<<< orphan*/  e1000_get_phy_cfg_done (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 e1000_phy_hw_reset(struct e1000_hw *hw)
{
	u32 ctrl, ctrl_ext;
	u32 led_ctrl;

	e_dbg("e1000_phy_hw_reset");

	e_dbg("Resetting Phy...\n");

	if (hw->mac_type > e1000_82543) {
		/* Read the device control register and assert the E1000_CTRL_PHY_RST
		 * bit. Then, take it out of reset.
		 * For e1000 hardware, we delay for 10ms between the assert
		 * and deassert.
		 */
		ctrl = er32(CTRL);
		ew32(CTRL, ctrl | E1000_CTRL_PHY_RST);
		E1000_WRITE_FLUSH();

		msleep(10);

		ew32(CTRL, ctrl);
		E1000_WRITE_FLUSH();

	} else {
		/* Read the Extended Device Control Register, assert the PHY_RESET_DIR
		 * bit to put the PHY into reset. Then, take it out of reset.
		 */
		ctrl_ext = er32(CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_SDP4_DIR;
		ctrl_ext &= ~E1000_CTRL_EXT_SDP4_DATA;
		ew32(CTRL_EXT, ctrl_ext);
		E1000_WRITE_FLUSH();
		msleep(10);
		ctrl_ext |= E1000_CTRL_EXT_SDP4_DATA;
		ew32(CTRL_EXT, ctrl_ext);
		E1000_WRITE_FLUSH();
	}
	udelay(150);

	if ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) {
		/* Configure activity LED after PHY reset */
		led_ctrl = er32(LEDCTL);
		led_ctrl &= IGP_ACTIVITY_LED_MASK;
		led_ctrl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
		ew32(LEDCTL, led_ctrl);
	}

	/* Wait for FW to finish PHY configuration. */
	return e1000_get_phy_cfg_done(hw);
}