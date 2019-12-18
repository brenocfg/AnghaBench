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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {scalar_t__ word_size; int opcode_bits; int address_bits; scalar_t__ page_size; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 scalar_t__ NVM_A8_OPCODE_SPI ; 
 scalar_t__ NVM_WREN_OPCODE_SPI ; 
 scalar_t__ NVM_WRITE_OPCODE_SPI ; 
 int /*<<< orphan*/  e1000_ready_nvm_eeprom (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_shift_out_eec_bits (struct e1000_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  e1000_standby_nvm (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 e1000e_write_nvm_spi(struct e1000_hw *hw, u16 offset, u16 words, u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	s32 ret_val = -E1000_ERR_NVM;
	u16 widx = 0;

	/* A check for invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	if ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) {
		e_dbg("nvm parameter(s) out of bounds\n");
		return -E1000_ERR_NVM;
	}

	while (widx < words) {
		u8 write_opcode = NVM_WRITE_OPCODE_SPI;

		ret_val = nvm->ops.acquire(hw);
		if (ret_val)
			return ret_val;

		ret_val = e1000_ready_nvm_eeprom(hw);
		if (ret_val) {
			nvm->ops.release(hw);
			return ret_val;
		}

		e1000_standby_nvm(hw);

		/* Send the WRITE ENABLE command (8 bit opcode) */
		e1000_shift_out_eec_bits(hw, NVM_WREN_OPCODE_SPI,
					 nvm->opcode_bits);

		e1000_standby_nvm(hw);

		/* Some SPI eeproms use the 8th address bit embedded in the
		 * opcode
		 */
		if ((nvm->address_bits == 8) && (offset >= 128))
			write_opcode |= NVM_A8_OPCODE_SPI;

		/* Send the Write command (8-bit opcode + addr) */
		e1000_shift_out_eec_bits(hw, write_opcode, nvm->opcode_bits);
		e1000_shift_out_eec_bits(hw, (u16)((offset + widx) * 2),
					 nvm->address_bits);

		/* Loop to allow for up to whole page write of eeprom */
		while (widx < words) {
			u16 word_out = data[widx];
			word_out = (word_out >> 8) | (word_out << 8);
			e1000_shift_out_eec_bits(hw, word_out, 16);
			widx++;

			if ((((offset + widx) * 2) % nvm->page_size) == 0) {
				e1000_standby_nvm(hw);
				break;
			}
		}
		usleep_range(10000, 20000);
		nvm->ops.release(hw);
	}

	return ret_val;
}