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
struct ixgbe_hw {scalar_t__ revision_id; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EEC ; 
 int IXGBE_EEC_FLUP ; 
 int IXGBE_EEC_SEC1VAL ; 
 scalar_t__ IXGBE_ERR_EEPROM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_poll_flash_update_done_X540 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_update_flash_X540(struct ixgbe_hw *hw)
{
	u32 flup;
	s32 status = IXGBE_ERR_EEPROM;

	status = ixgbe_poll_flash_update_done_X540(hw);
	if (status == IXGBE_ERR_EEPROM) {
		hw_dbg(hw, "Flash update time out\n");
		goto out;
	}

	flup = IXGBE_READ_REG(hw, IXGBE_EEC) | IXGBE_EEC_FLUP;
	IXGBE_WRITE_REG(hw, IXGBE_EEC, flup);

	status = ixgbe_poll_flash_update_done_X540(hw);
	if (status == 0)
		hw_dbg(hw, "Flash update complete\n");
	else
		hw_dbg(hw, "Flash update time out\n");

	if (hw->revision_id == 0) {
		flup = IXGBE_READ_REG(hw, IXGBE_EEC);

		if (flup & IXGBE_EEC_SEC1VAL) {
			flup |= IXGBE_EEC_FLUP;
			IXGBE_WRITE_REG(hw, IXGBE_EEC, flup);
		}

		status = ixgbe_poll_flash_update_done_X540(hw);
		if (status == 0)
			hw_dbg(hw, "Flash update complete\n");
		else
			hw_dbg(hw, "Flash update time out\n");
	}
out:
	return status;
}