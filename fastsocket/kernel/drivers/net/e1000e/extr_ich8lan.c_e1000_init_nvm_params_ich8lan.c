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
typedef  int u32 ;
typedef  size_t u16 ;
struct e1000_nvm_info {int flash_base_addr; int flash_bank_size; size_t word_size; int /*<<< orphan*/  type; } ;
struct e1000_dev_spec_ich8lan {TYPE_2__* shadow_ram; } ;
struct TYPE_3__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {int /*<<< orphan*/  flash_address; TYPE_1__ dev_spec; struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int modified; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 size_t E1000_ICH8_SHADOW_RAM_WORDS ; 
 int FLASH_GFPREG_BASE_MASK ; 
 int FLASH_SECTOR_ADDR_SHIFT ; 
 int /*<<< orphan*/  ICH_FLASH_GFPREG ; 
 int /*<<< orphan*/  e1000_nvm_flash_sw ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32flash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_init_nvm_params_ich8lan(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 gfpreg, sector_base_addr, sector_end_addr;
	u16 i;

	/* Can't read flash registers if the register set isn't mapped. */
	if (!hw->flash_address) {
		e_dbg("ERROR: Flash registers not mapped\n");
		return -E1000_ERR_CONFIG;
	}

	nvm->type = e1000_nvm_flash_sw;

	gfpreg = er32flash(ICH_FLASH_GFPREG);

	/* sector_X_addr is a "sector"-aligned address (4096 bytes)
	 * Add 1 to sector_end_addr since this sector is included in
	 * the overall size.
	 */
	sector_base_addr = gfpreg & FLASH_GFPREG_BASE_MASK;
	sector_end_addr = ((gfpreg >> 16) & FLASH_GFPREG_BASE_MASK) + 1;

	/* flash_base_addr is byte-aligned */
	nvm->flash_base_addr = sector_base_addr << FLASH_SECTOR_ADDR_SHIFT;

	/* find total size of the NVM, then cut in half since the total
	 * size represents two separate NVM banks.
	 */
	nvm->flash_bank_size = ((sector_end_addr - sector_base_addr)
				<< FLASH_SECTOR_ADDR_SHIFT);
	nvm->flash_bank_size /= 2;
	/* Adjust to word count */
	nvm->flash_bank_size /= sizeof(u16);

	nvm->word_size = E1000_ICH8_SHADOW_RAM_WORDS;

	/* Clear shadow ram */
	for (i = 0; i < nvm->word_size; i++) {
		dev_spec->shadow_ram[i].modified = false;
		dev_spec->shadow_ram[i].value = 0xFFFF;
	}

	return 0;
}