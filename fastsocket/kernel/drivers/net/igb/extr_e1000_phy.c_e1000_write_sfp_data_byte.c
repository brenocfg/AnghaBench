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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int /*<<< orphan*/  E1000_I2CCMD ; 
 scalar_t__ E1000_I2CCMD_ERROR ; 
 scalar_t__ E1000_I2CCMD_OPCODE_READ ; 
 scalar_t__ E1000_I2CCMD_OPCODE_WRITE ; 
 scalar_t__ E1000_I2CCMD_PHY_TIMEOUT ; 
 scalar_t__ E1000_I2CCMD_READY ; 
 scalar_t__ E1000_I2CCMD_REG_ADDR_SHIFT ; 
 scalar_t__ E1000_I2CCMD_SFP_DIAG_ADDR (int) ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,scalar_t__) ; 

s32 e1000_write_sfp_data_byte(struct e1000_hw *hw, u16 offset, u8 data)
{
	u32 i = 0;
	u32 i2ccmd = 0;
	u32 data_local = 0;

	if (offset > E1000_I2CCMD_SFP_DIAG_ADDR(255)) {
		hw_dbg("I2CCMD command address exceeds upper limit\n");
		return -E1000_ERR_PHY;
	}
	/* The programming interface is 16 bits wide
	 * so we need to read the whole word first
	 * then update appropriate byte lane and write
	 * the updated word back.
	 */
	/* Set up Op-code, EEPROM Address,in the I2CCMD
	 * register. The MAC will take care of interfacing
	 * with an EEPROM to write the data given.
	 */
	i2ccmd = ((offset << E1000_I2CCMD_REG_ADDR_SHIFT) |
		  E1000_I2CCMD_OPCODE_READ);
	/* Set a command to read single word */
	wr32(E1000_I2CCMD, i2ccmd);
	for (i = 0; i < E1000_I2CCMD_PHY_TIMEOUT; i++) {
		udelay(50);
		/* Poll the ready bit to see if lastly
		 * launched I2C operation completed
		 */
		i2ccmd = rd32(E1000_I2CCMD);
		if (i2ccmd & E1000_I2CCMD_READY) {
			/* Check if this is READ or WRITE phase */
			if ((i2ccmd & E1000_I2CCMD_OPCODE_READ) ==
			    E1000_I2CCMD_OPCODE_READ) {
				/* Write the selected byte
				 * lane and update whole word
				 */
				data_local = i2ccmd & 0xFF00;
				data_local |= data;
				i2ccmd = ((offset <<
					E1000_I2CCMD_REG_ADDR_SHIFT) |
					E1000_I2CCMD_OPCODE_WRITE | data_local);
				wr32(E1000_I2CCMD, i2ccmd);
			} else {
				break;
			}
		}
	}
	if (!(i2ccmd & E1000_I2CCMD_READY)) {
		hw_dbg("I2CCMD Write did not complete\n");
		return -E1000_ERR_PHY;
	}
	if (i2ccmd & E1000_I2CCMD_ERROR) {
		hw_dbg("I2CCMD Error bit set\n");
		return -E1000_ERR_PHY;
	}
	return 0;
}