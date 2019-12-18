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
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  update; int /*<<< orphan*/  validate; int /*<<< orphan*/  read; int /*<<< orphan*/  write; int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {int word_size; int opcode_bits; int delay_usec; int override; int page_size; int address_bits; TYPE_2__ ops; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_ADDR_BITS ; 
 int E1000_EECD_SIZE_EX_MASK ; 
 int E1000_EECD_SIZE_EX_SHIFT ; 
 scalar_t__ NVM_WORD_SIZE_BASE_SHIFT ; 
#define  e1000_82580 132 
#define  e1000_i350 131 
#define  e1000_i354 130 
 int /*<<< orphan*/  e1000_nvm_eeprom_spi ; 
#define  e1000_nvm_override_spi_large 129 
#define  e1000_nvm_override_spi_small 128 
 int /*<<< orphan*/  igb_acquire_nvm_82575 ; 
 int /*<<< orphan*/  igb_read_nvm_eerd ; 
 int /*<<< orphan*/  igb_read_nvm_spi ; 
 int /*<<< orphan*/  igb_release_nvm_82575 ; 
 int /*<<< orphan*/  igb_update_nvm_checksum ; 
 int /*<<< orphan*/  igb_update_nvm_checksum_82580 ; 
 int /*<<< orphan*/  igb_update_nvm_checksum_i350 ; 
 int /*<<< orphan*/  igb_validate_nvm_checksum ; 
 int /*<<< orphan*/  igb_validate_nvm_checksum_82580 ; 
 int /*<<< orphan*/  igb_validate_nvm_checksum_i350 ; 
 int /*<<< orphan*/  igb_write_nvm_spi ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_init_nvm_params_82575(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(E1000_EECD);
	u16 size;

	size = (u16)((eecd & E1000_EECD_SIZE_EX_MASK) >>
		     E1000_EECD_SIZE_EX_SHIFT);

	/* Added to a constant, "size" becomes the left-shift value
	 * for setting word_size.
	 */
	size += NVM_WORD_SIZE_BASE_SHIFT;

	/* Just in case size is out of range, cap it to the largest
	 * EEPROM size supported
	 */
	if (size > 15)
		size = 15;

	nvm->word_size = 1 << size;
	nvm->opcode_bits = 8;
	nvm->delay_usec = 1;

	switch (nvm->override) {
	case e1000_nvm_override_spi_large:
		nvm->page_size = 32;
		nvm->address_bits = 16;
		break;
	case e1000_nvm_override_spi_small:
		nvm->page_size = 8;
		nvm->address_bits = 8;
		break;
	default:
		nvm->page_size = eecd & E1000_EECD_ADDR_BITS ? 32 : 8;
		nvm->address_bits = eecd & E1000_EECD_ADDR_BITS ?
				    16 : 8;
		break;
	}
	if (nvm->word_size == (1 << 15))
		nvm->page_size = 128;

	nvm->type = e1000_nvm_eeprom_spi;

	/* NVM Function Pointers */
	nvm->ops.acquire = igb_acquire_nvm_82575;
	nvm->ops.release = igb_release_nvm_82575;
	nvm->ops.write = igb_write_nvm_spi;
	nvm->ops.validate = igb_validate_nvm_checksum;
	nvm->ops.update = igb_update_nvm_checksum;
	if (nvm->word_size < (1 << 15))
		nvm->ops.read = igb_read_nvm_eerd;
	else
		nvm->ops.read = igb_read_nvm_spi;

	/* override generic family function pointers for specific descendants */
	switch (hw->mac.type) {
	case e1000_82580:
		nvm->ops.validate = igb_validate_nvm_checksum_82580;
		nvm->ops.update = igb_update_nvm_checksum_82580;
		break;
	case e1000_i354:
	case e1000_i350:
		nvm->ops.validate = igb_validate_nvm_checksum_i350;
		nvm->ops.update = igb_update_nvm_checksum_i350;
		break;
	default:
		break;
	}

	return 0;
}