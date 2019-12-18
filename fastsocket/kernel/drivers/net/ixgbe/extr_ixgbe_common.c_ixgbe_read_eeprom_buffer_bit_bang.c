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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int address_bits; } ;
struct ixgbe_hw {TYPE_1__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBE_EEPROM_A8_OPCODE_SPI ; 
 int IXGBE_EEPROM_OPCODE_BITS ; 
 int IXGBE_EEPROM_READ_OPCODE_SPI ; 
 scalar_t__ IXGBE_ERR_EEPROM ; 
 scalar_t__ ixgbe_acquire_eeprom (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_ready_eeprom (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_release_eeprom (struct ixgbe_hw*) ; 
 int ixgbe_shift_in_eeprom_bits (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_shift_out_eeprom_bits (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  ixgbe_standby_eeprom (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_read_eeprom_buffer_bit_bang(struct ixgbe_hw *hw, u16 offset,
					     u16 words, u16 *data)
{
	s32 status;
	u16 word_in;
	u8 read_opcode = IXGBE_EEPROM_READ_OPCODE_SPI;
	u16 i;

	/* Prepare the EEPROM for reading  */
	status = ixgbe_acquire_eeprom(hw);

	if (status == 0) {
		if (ixgbe_ready_eeprom(hw) != 0) {
			ixgbe_release_eeprom(hw);
			status = IXGBE_ERR_EEPROM;
		}
	}

	if (status == 0) {
		for (i = 0; i < words; i++) {
			ixgbe_standby_eeprom(hw);
			/*
			 * Some SPI eeproms use the 8th address bit embedded
			 * in the opcode
			 */
			if ((hw->eeprom.address_bits == 8) &&
			    ((offset + i) >= 128))
				read_opcode |= IXGBE_EEPROM_A8_OPCODE_SPI;

			/* Send the READ command (opcode + addr) */
			ixgbe_shift_out_eeprom_bits(hw, read_opcode,
						    IXGBE_EEPROM_OPCODE_BITS);
			ixgbe_shift_out_eeprom_bits(hw, (u16)((offset + i) * 2),
						    hw->eeprom.address_bits);

			/* Read the data. */
			word_in = ixgbe_shift_in_eeprom_bits(hw, 16);
			data[i] = (word_in >> 8) | (word_in << 8);
		}

		/* End this read operation */
		ixgbe_release_eeprom(hw);
	}

	return status;
}