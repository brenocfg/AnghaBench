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
struct e1000_hw {int subsystem_vendor_id; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_EEPROM ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ EEPROM_CHECKSUM_REG ; 
 scalar_t__ EEPROM_SUM ; 
 scalar_t__ e1000_read_eeprom (struct e1000_hw*,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

s32 e1000_validate_eeprom_checksum(struct e1000_hw *hw)
{
	u16 checksum = 0;
	u16 i, eeprom_data;

	e_dbg("e1000_validate_eeprom_checksum");

	for (i = 0; i < (EEPROM_CHECKSUM_REG + 1); i++) {
		if (e1000_read_eeprom(hw, i, 1, &eeprom_data) < 0) {
			e_dbg("EEPROM Read Error\n");
			return -E1000_ERR_EEPROM;
		}
		checksum += eeprom_data;
	}

#ifdef CONFIG_PARISC
	/* This is a signature and not a checksum on HP c8000 */
	if ((hw->subsystem_vendor_id == 0x103C) && (eeprom_data == 0x16d6))
		return E1000_SUCCESS;

#endif
	if (checksum == (u16) EEPROM_SUM)
		return E1000_SUCCESS;
	else {
		e_dbg("EEPROM Checksum Invalid\n");
		return -E1000_ERR_EEPROM;
	}
}