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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_EEPROM_RW_REG_DONE ; 
 int /*<<< orphan*/  IXGBE_EERD ; 
 scalar_t__ IXGBE_EERD_EEWR_ATTEMPTS ; 
 int /*<<< orphan*/  IXGBE_EEWR ; 
 scalar_t__ IXGBE_ERR_EEPROM ; 
 scalar_t__ IXGBE_NVM_POLL_READ ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbe_poll_eerd_eewr_done(struct ixgbe_hw *hw, u32 ee_reg)
{
	u32 i;
	u32 reg;
	s32 status = IXGBE_ERR_EEPROM;

	for (i = 0; i < IXGBE_EERD_EEWR_ATTEMPTS; i++) {
		if (ee_reg == IXGBE_NVM_POLL_READ)
			reg = IXGBE_READ_REG(hw, IXGBE_EERD);
		else
			reg = IXGBE_READ_REG(hw, IXGBE_EEWR);

		if (reg & IXGBE_EEPROM_RW_REG_DONE) {
			status = 0;
			break;
		}
		udelay(5);
	}
	return status;
}