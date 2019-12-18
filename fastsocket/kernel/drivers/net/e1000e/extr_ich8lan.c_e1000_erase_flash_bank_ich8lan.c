#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int berasesz; int /*<<< orphan*/  flcdone; scalar_t__ flcerr; } ;
union ich8_hws_flash_status {TYPE_2__ hsf_status; void* regval; } ;
struct TYPE_3__ {int /*<<< orphan*/  flcycle; } ;
union ich8_hws_flash_ctrl {void* regval; TYPE_1__ hsf_ctrl; } ;
typedef  scalar_t__ u32 ;
struct e1000_nvm_info {int flash_bank_size; scalar_t__ flash_base_addr; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_NVM ; 
 int /*<<< orphan*/  ICH_CYCLE_ERASE ; 
 scalar_t__ ICH_FLASH_CYCLE_REPEAT_COUNT ; 
 int /*<<< orphan*/  ICH_FLASH_ERASE_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  ICH_FLASH_FADDR ; 
 int /*<<< orphan*/  ICH_FLASH_HSFCTL ; 
 int /*<<< orphan*/  ICH_FLASH_HSFSTS ; 
 scalar_t__ ICH_FLASH_SEG_SIZE_256 ; 
 scalar_t__ ICH_FLASH_SEG_SIZE_4K ; 
 scalar_t__ ICH_FLASH_SEG_SIZE_64K ; 
 scalar_t__ ICH_FLASH_SEG_SIZE_8K ; 
 scalar_t__ e1000_flash_cycle_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_flash_cycle_init_ich8lan (struct e1000_hw*) ; 
 void* er16flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew16flash (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ew32flash (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s32 e1000_erase_flash_bank_ich8lan(struct e1000_hw *hw, u32 bank)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	union ich8_hws_flash_status hsfsts;
	union ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	/* bank size is in 16bit words - adjust to bytes */
	u32 flash_bank_size = nvm->flash_bank_size * 2;
	s32 ret_val;
	s32 count = 0;
	s32 j, iteration, sector_size;

	hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);

	/* Determine HW Sector size: Read BERASE bits of hw flash status
	 * register
	 * 00: The Hw sector is 256 bytes, hence we need to erase 16
	 *     consecutive sectors.  The start index for the nth Hw sector
	 *     can be calculated as = bank * 4096 + n * 256
	 * 01: The Hw sector is 4K bytes, hence we need to erase 1 sector.
	 *     The start index for the nth Hw sector can be calculated
	 *     as = bank * 4096
	 * 10: The Hw sector is 8K bytes, nth sector = bank * 8192
	 *     (ich9 only, otherwise error condition)
	 * 11: The Hw sector is 64K bytes, nth sector = bank * 65536
	 */
	switch (hsfsts.hsf_status.berasesz) {
	case 0:
		/* Hw sector size 256 */
		sector_size = ICH_FLASH_SEG_SIZE_256;
		iteration = flash_bank_size / ICH_FLASH_SEG_SIZE_256;
		break;
	case 1:
		sector_size = ICH_FLASH_SEG_SIZE_4K;
		iteration = 1;
		break;
	case 2:
		sector_size = ICH_FLASH_SEG_SIZE_8K;
		iteration = 1;
		break;
	case 3:
		sector_size = ICH_FLASH_SEG_SIZE_64K;
		iteration = 1;
		break;
	default:
		return -E1000_ERR_NVM;
	}

	/* Start with the base address, then add the sector offset. */
	flash_linear_addr = hw->nvm.flash_base_addr;
	flash_linear_addr += (bank) ? flash_bank_size : 0;

	for (j = 0; j < iteration; j++) {
		do {
			/* Steps */
			ret_val = e1000_flash_cycle_init_ich8lan(hw);
			if (ret_val)
				return ret_val;

			/* Write a value 11 (block Erase) in Flash
			 * Cycle field in hw flash control
			 */
			hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);
			hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_ERASE;
			ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

			/* Write the last 24 bits of an index within the
			 * block into Flash Linear address field in Flash
			 * Address.
			 */
			flash_linear_addr += (j * sector_size);
			ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

			ret_val = e1000_flash_cycle_ich8lan(hw,
					       ICH_FLASH_ERASE_COMMAND_TIMEOUT);
			if (!ret_val)
				break;

			/* Check if FCERR is set to 1.  If 1,
			 * clear it and try the whole sequence
			 * a few more times else Done
			 */
			hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
			if (hsfsts.hsf_status.flcerr)
				/* repeat for some time before giving up */
				continue;
			else if (!hsfsts.hsf_status.flcdone)
				return ret_val;
		} while (++count < ICH_FLASH_CYCLE_REPEAT_COUNT);
	}

	return 0;
}