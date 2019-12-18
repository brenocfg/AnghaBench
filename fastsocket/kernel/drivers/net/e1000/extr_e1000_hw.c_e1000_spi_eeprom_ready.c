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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  opcode_bits; } ;
struct e1000_hw {TYPE_1__ eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_EEPROM ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ EEPROM_MAX_RETRY_SPI ; 
 int /*<<< orphan*/  EEPROM_RDSR_OPCODE_SPI ; 
 int EEPROM_STATUS_RDY_SPI ; 
 scalar_t__ e1000_shift_in_ee_bits (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1000_shift_out_ee_bits (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_standby_eeprom (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_spi_eeprom_ready(struct e1000_hw *hw)
{
	u16 retry_count = 0;
	u8 spi_stat_reg;

	e_dbg("e1000_spi_eeprom_ready");

	/* Read "Status Register" repeatedly until the LSB is cleared.  The
	 * EEPROM will signal that the command has been completed by clearing
	 * bit 0 of the internal status register.  If it's not cleared within
	 * 5 milliseconds, then error out.
	 */
	retry_count = 0;
	do {
		e1000_shift_out_ee_bits(hw, EEPROM_RDSR_OPCODE_SPI,
					hw->eeprom.opcode_bits);
		spi_stat_reg = (u8) e1000_shift_in_ee_bits(hw, 8);
		if (!(spi_stat_reg & EEPROM_STATUS_RDY_SPI))
			break;

		udelay(5);
		retry_count += 5;

		e1000_standby_eeprom(hw);
	} while (retry_count < EEPROM_MAX_RETRY_SPI);

	/* ATMEL SPI write time could vary from 0-20mSec on 3.3V devices (and
	 * only 0-5mSec on 5V devices)
	 */
	if (retry_count >= EEPROM_MAX_RETRY_SPI) {
		e_dbg("SPI EEPROM Status error\n");
		return -E1000_ERR_EEPROM;
	}

	return E1000_SUCCESS;
}