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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,scalar_t__,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;

/* Variables and functions */
 scalar_t__ IXGBE_EEPROM_CHECKSUM ; 
 scalar_t__ IXGBE_EEPROM_SUM ; 
 scalar_t__ IXGBE_FW_PTR ; 
 scalar_t__ IXGBE_PCIE_ANALOG_PTR ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,scalar_t__,scalar_t__*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,scalar_t__,scalar_t__*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,scalar_t__,scalar_t__*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,scalar_t__,scalar_t__*) ; 

u16 ixgbe_calc_eeprom_checksum_generic(struct ixgbe_hw *hw)
{
	u16 i;
	u16 j;
	u16 checksum = 0;
	u16 length = 0;
	u16 pointer = 0;
	u16 word = 0;

	/* Include 0x0-0x3F in the checksum */
	for (i = 0; i < IXGBE_EEPROM_CHECKSUM; i++) {
		if (hw->eeprom.ops.read(hw, i, &word) != 0) {
			hw_dbg(hw, "EEPROM read failed\n");
			break;
		}
		checksum += word;
	}

	/* Include all data from pointers except for the fw pointer */
	for (i = IXGBE_PCIE_ANALOG_PTR; i < IXGBE_FW_PTR; i++) {
		hw->eeprom.ops.read(hw, i, &pointer);

		/* Make sure the pointer seems valid */
		if (pointer != 0xFFFF && pointer != 0) {
			hw->eeprom.ops.read(hw, pointer, &length);

			if (length != 0xFFFF && length != 0) {
				for (j = pointer+1; j <= pointer+length; j++) {
					hw->eeprom.ops.read(hw, j, &word);
					checksum += word;
				}
			}
		}
	}

	checksum = (u16)IXGBE_EEPROM_SUM - checksum;

	return checksum;
}