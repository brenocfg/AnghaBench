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
typedef  int u32 ;
struct atl2_hw {int dummy; } ;

/* Variables and functions */
 int ATL2_READ_REG (struct atl2_hw*,int /*<<< orphan*/ ) ; 
 int ATL2_READ_REGW (struct atl2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_PCIE_CAP_LIST ; 
 int /*<<< orphan*/  REG_SPI_FLASH_CTRL ; 
 int SPI_FLASH_CTRL_EN_VPD ; 

__attribute__((used)) static int atl2_check_eeprom_exist(struct atl2_hw *hw)
{
	u32 value;

	value = ATL2_READ_REG(hw, REG_SPI_FLASH_CTRL);
	if (value & SPI_FLASH_CTRL_EN_VPD) {
		value &= ~SPI_FLASH_CTRL_EN_VPD;
		ATL2_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);
	}
	value = ATL2_READ_REGW(hw, REG_PCIE_CAP_LIST);
	return ((value & 0xFF00) == 0x6C00) ? 0 : 1;
}