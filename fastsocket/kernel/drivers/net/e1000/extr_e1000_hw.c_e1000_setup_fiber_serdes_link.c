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
struct e1000_hw {scalar_t__ media_type; scalar_t__ mac_type; int fc; int txcw; int autoneg_failed; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_LRST ; 
 int E1000_CTRL_SWDPIN1 ; 
 scalar_t__ E1000_ERR_CONFIG ; 
#define  E1000_FC_FULL 131 
#define  E1000_FC_NONE 130 
#define  E1000_FC_RX_PAUSE 129 
#define  E1000_FC_TX_PAUSE 128 
 int E1000_STATUS_LU ; 
 scalar_t__ E1000_SUCCESS ; 
 int E1000_TXCW_ANE ; 
 int E1000_TXCW_ASM_DIR ; 
 int E1000_TXCW_FD ; 
 int E1000_TXCW_PAUSE_MASK ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int LINK_UP_TIMEOUT ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TXCW ; 
 scalar_t__ e1000_82544 ; 
 scalar_t__ e1000_adjust_serdes_amplitude (struct e1000_hw*) ; 
 scalar_t__ e1000_check_for_link (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_config_collision_dist (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_set_vco_speed (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_setup_fiber_serdes_link(struct e1000_hw *hw)
{
	u32 ctrl;
	u32 status;
	u32 txcw = 0;
	u32 i;
	u32 signal = 0;
	s32 ret_val;

	e_dbg("e1000_setup_fiber_serdes_link");

	/* On adapters with a MAC newer than 82544, SWDP 1 will be
	 * set when the optics detect a signal. On older adapters, it will be
	 * cleared when there is a signal.  This applies to fiber media only.
	 * If we're on serdes media, adjust the output amplitude to value
	 * set in the EEPROM.
	 */
	ctrl = er32(CTRL);
	if (hw->media_type == e1000_media_type_fiber)
		signal = (hw->mac_type > e1000_82544) ? E1000_CTRL_SWDPIN1 : 0;

	ret_val = e1000_adjust_serdes_amplitude(hw);
	if (ret_val)
		return ret_val;

	/* Take the link out of reset */
	ctrl &= ~(E1000_CTRL_LRST);

	/* Adjust VCO speed to improve BER performance */
	ret_val = e1000_set_vco_speed(hw);
	if (ret_val)
		return ret_val;

	e1000_config_collision_dist(hw);

	/* Check for a software override of the flow control settings, and setup
	 * the device accordingly.  If auto-negotiation is enabled, then software
	 * will have to set the "PAUSE" bits to the correct value in the Tranmsit
	 * Config Word Register (TXCW) and re-start auto-negotiation.  However, if
	 * auto-negotiation is disabled, then software will have to manually
	 * configure the two flow control enable bits in the CTRL register.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive pause frames, but
	 *          not send pause frames).
	 *      2:  Tx flow control is enabled (we can send pause frames but we do
	 *          not support receiving pause frames).
	 *      3:  Both Rx and TX flow control (symmetric) are enabled.
	 */
	switch (hw->fc) {
	case E1000_FC_NONE:
		/* Flow control is completely disabled by a software over-ride. */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD);
		break;
	case E1000_FC_RX_PAUSE:
		/* RX Flow control is enabled and TX Flow control is disabled by a
		 * software over-ride. Since there really isn't a way to advertise
		 * that we are capable of RX Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric RX PAUSE. Later, we will
		 *  disable the adapter's ability to send PAUSE frames.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		break;
	case E1000_FC_TX_PAUSE:
		/* TX Flow control is enabled, and RX Flow control is disabled, by a
		 * software over-ride.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_ASM_DIR);
		break;
	case E1000_FC_FULL:
		/* Flow control (both RX and TX) is enabled by a software over-ride. */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		break;
	default:
		e_dbg("Flow control param set incorrectly\n");
		return -E1000_ERR_CONFIG;
		break;
	}

	/* Since auto-negotiation is enabled, take the link out of reset (the link
	 * will be in reset, because we previously reset the chip). This will
	 * restart auto-negotiation.  If auto-negotiation is successful then the
	 * link-up status bit will be set and the flow control enable bits (RFCE
	 * and TFCE) will be set according to their negotiated value.
	 */
	e_dbg("Auto-negotiation enabled\n");

	ew32(TXCW, txcw);
	ew32(CTRL, ctrl);
	E1000_WRITE_FLUSH();

	hw->txcw = txcw;
	msleep(1);

	/* If we have a signal (the cable is plugged in) then poll for a "Link-Up"
	 * indication in the Device Status Register.  Time-out if a link isn't
	 * seen in 500 milliseconds seconds (Auto-negotiation should complete in
	 * less than 500 milliseconds even if the other end is doing it in SW).
	 * For internal serdes, we just assume a signal is present, then poll.
	 */
	if (hw->media_type == e1000_media_type_internal_serdes ||
	    (er32(CTRL) & E1000_CTRL_SWDPIN1) == signal) {
		e_dbg("Looking for Link\n");
		for (i = 0; i < (LINK_UP_TIMEOUT / 10); i++) {
			msleep(10);
			status = er32(STATUS);
			if (status & E1000_STATUS_LU)
				break;
		}
		if (i == (LINK_UP_TIMEOUT / 10)) {
			e_dbg("Never got a valid link from auto-neg!!!\n");
			hw->autoneg_failed = 1;
			/* AutoNeg failed to achieve a link, so we'll call
			 * e1000_check_for_link. This routine will force the link up if
			 * we detect a signal. This will allow us to communicate with
			 * non-autonegotiating link partners.
			 */
			ret_val = e1000_check_for_link(hw);
			if (ret_val) {
				e_dbg("Error while checking for link\n");
				return ret_val;
			}
			hw->autoneg_failed = 0;
		} else {
			hw->autoneg_failed = 0;
			e_dbg("Valid Link Found\n");
		}
	} else {
		e_dbg("No Signal Detected\n");
	}
	return E1000_SUCCESS;
}