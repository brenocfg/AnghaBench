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
typedef  scalar_t__ u16 ;
struct e1000_eeprom_info {scalar_t__ word_size; scalar_t__ type; } ;
struct e1000_hw {scalar_t__ mac_type; struct e1000_eeprom_info eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_EEPROM ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  GBE_CONFIG_BASE_VIRT ; 
 int /*<<< orphan*/  GBE_CONFIG_FLASH_WRITE (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ e1000_acquire_eeprom (struct e1000_hw*) ; 
 scalar_t__ e1000_ce4100 ; 
 scalar_t__ e1000_eeprom_microwire ; 
 int /*<<< orphan*/  e1000_init_eeprom_params (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_release_eeprom (struct e1000_hw*) ; 
 scalar_t__ e1000_write_eeprom_microwire (struct e1000_hw*,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ e1000_write_eeprom_spi (struct e1000_hw*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_do_write_eeprom(struct e1000_hw *hw, u16 offset, u16 words,
				 u16 *data)
{
	struct e1000_eeprom_info *eeprom = &hw->eeprom;
	s32 status = 0;

	e_dbg("e1000_write_eeprom");

	if (hw->mac_type == e1000_ce4100) {
		GBE_CONFIG_FLASH_WRITE(GBE_CONFIG_BASE_VIRT, offset, words,
		                       data);
		return E1000_SUCCESS;
	}

	/* If eeprom is not yet detected, do so now */
	if (eeprom->word_size == 0)
		e1000_init_eeprom_params(hw);

	/* A check for invalid values:  offset too large, too many words, and not
	 * enough words.
	 */
	if ((offset >= eeprom->word_size)
	    || (words > eeprom->word_size - offset) || (words == 0)) {
		e_dbg("\"words\" parameter out of bounds\n");
		return -E1000_ERR_EEPROM;
	}

	/* Prepare the EEPROM for writing  */
	if (e1000_acquire_eeprom(hw) != E1000_SUCCESS)
		return -E1000_ERR_EEPROM;

	if (eeprom->type == e1000_eeprom_microwire) {
		status = e1000_write_eeprom_microwire(hw, offset, words, data);
	} else {
		status = e1000_write_eeprom_spi(hw, offset, words, data);
		msleep(10);
	}

	/* Done with writing */
	e1000_release_eeprom(hw);

	return status;
}