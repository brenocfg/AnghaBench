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
typedef  int u32 ;
struct TYPE_2__ {int type; int pause_time; int low_water; int high_water; scalar_t__ send_xon; } ;
struct ixgb_hw {TYPE_1__ fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTRL0 ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  FCRTH ; 
 int /*<<< orphan*/  FCRTL ; 
 int IXGB_CTRL0_CMDC ; 
 int IXGB_CTRL0_RPE ; 
 int IXGB_CTRL0_TPE ; 
 int IXGB_FCRTL_XONE ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PAP ; 
#define  ixgb_fc_full 131 
#define  ixgb_fc_none 130 
#define  ixgb_fc_rx_pause 129 
#define  ixgb_fc_tx_pause 128 

__attribute__((used)) static bool
ixgb_setup_fc(struct ixgb_hw *hw)
{
	u32 ctrl_reg;
	u32 pap_reg = 0;   /* by default, assume no pause time */
	bool status = true;

	DEBUGFUNC("ixgb_setup_fc");

	/* Get the current control reg 0 settings */
	ctrl_reg = IXGB_READ_REG(hw, CTRL0);

	/* Clear the Receive Pause Enable and Transmit Pause Enable bits */
	ctrl_reg &= ~(IXGB_CTRL0_RPE | IXGB_CTRL0_TPE);

	/* The possible values of the "flow_control" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive pause frames
	 *          but not send pause frames).
	 *      2:  Tx flow control is enabled (we can send pause frames
	 *          but we do not support receiving pause frames).
	 *      3:  Both Rx and TX flow control (symmetric) are enabled.
	 *  other:  Invalid.
	 */
	switch (hw->fc.type) {
	case ixgb_fc_none:	/* 0 */
		/* Set CMDC bit to disable Rx Flow control */
		ctrl_reg |= (IXGB_CTRL0_CMDC);
		break;
	case ixgb_fc_rx_pause:	/* 1 */
		/* RX Flow control is enabled, and TX Flow control is
		 * disabled.
		 */
		ctrl_reg |= (IXGB_CTRL0_RPE);
		break;
	case ixgb_fc_tx_pause:	/* 2 */
		/* TX Flow control is enabled, and RX Flow control is
		 * disabled, by a software over-ride.
		 */
		ctrl_reg |= (IXGB_CTRL0_TPE);
		pap_reg = hw->fc.pause_time;
		break;
	case ixgb_fc_full:	/* 3 */
		/* Flow control (both RX and TX) is enabled by a software
		 * over-ride.
		 */
		ctrl_reg |= (IXGB_CTRL0_RPE | IXGB_CTRL0_TPE);
		pap_reg = hw->fc.pause_time;
		break;
	default:
		/* We should never get here.  The value should be 0-3. */
		DEBUGOUT("Flow control param set incorrectly\n");
		ASSERT(0);
		break;
	}

	/* Write the new settings */
	IXGB_WRITE_REG(hw, CTRL0, ctrl_reg);

	if (pap_reg != 0)
		IXGB_WRITE_REG(hw, PAP, pap_reg);

	/* Set the flow control receive threshold registers.  Normally,
	 * these registers will be set to a default threshold that may be
	 * adjusted later by the driver's runtime code.  However, if the
	 * ability to transmit pause frames in not enabled, then these
	 * registers will be set to 0.
	 */
	if (!(hw->fc.type & ixgb_fc_tx_pause)) {
		IXGB_WRITE_REG(hw, FCRTL, 0);
		IXGB_WRITE_REG(hw, FCRTH, 0);
	} else {
	   /* We need to set up the Receive Threshold high and low water
	    * marks as well as (optionally) enabling the transmission of XON
	    * frames. */
		if (hw->fc.send_xon) {
			IXGB_WRITE_REG(hw, FCRTL,
				(hw->fc.low_water | IXGB_FCRTL_XONE));
		} else {
			IXGB_WRITE_REG(hw, FCRTL, hw->fc.low_water);
		}
		IXGB_WRITE_REG(hw, FCRTH, hw->fc.high_water);
	}
	return (status);
}