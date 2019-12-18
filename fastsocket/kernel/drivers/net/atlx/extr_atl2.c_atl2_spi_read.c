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
 int /*<<< orphan*/  ATL2_WRITE_REG (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 
 int CUSTOM_SPI_CLK_HI ; 
 int CUSTOM_SPI_CLK_LO ; 
 int CUSTOM_SPI_CS_HI ; 
 int CUSTOM_SPI_CS_HOLD ; 
 int CUSTOM_SPI_CS_SETUP ; 
 int /*<<< orphan*/  REG_SPI_ADDR ; 
 int /*<<< orphan*/  REG_SPI_DATA ; 
 int /*<<< orphan*/  REG_SPI_FLASH_CTRL ; 
 int SPI_FLASH_CTRL_CLK_HI_MASK ; 
 int SPI_FLASH_CTRL_CLK_HI_SHIFT ; 
 int SPI_FLASH_CTRL_CLK_LO_MASK ; 
 int SPI_FLASH_CTRL_CLK_LO_SHIFT ; 
 int SPI_FLASH_CTRL_CS_HI_MASK ; 
 int SPI_FLASH_CTRL_CS_HI_SHIFT ; 
 int SPI_FLASH_CTRL_CS_HOLD_MASK ; 
 int SPI_FLASH_CTRL_CS_HOLD_SHIFT ; 
 int SPI_FLASH_CTRL_CS_SETUP_MASK ; 
 int SPI_FLASH_CTRL_CS_SETUP_SHIFT ; 
 int SPI_FLASH_CTRL_INS_MASK ; 
 int SPI_FLASH_CTRL_INS_SHIFT ; 
 int SPI_FLASH_CTRL_START ; 
 int SPI_FLASH_CTRL_WAIT_READY ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static bool atl2_spi_read(struct atl2_hw *hw, u32 addr, u32 *buf)
{
	int i;
	u32 value;

	ATL2_WRITE_REG(hw, REG_SPI_DATA, 0);
	ATL2_WRITE_REG(hw, REG_SPI_ADDR, addr);

	value = SPI_FLASH_CTRL_WAIT_READY |
		(CUSTOM_SPI_CS_SETUP & SPI_FLASH_CTRL_CS_SETUP_MASK) <<
			SPI_FLASH_CTRL_CS_SETUP_SHIFT |
		(CUSTOM_SPI_CLK_HI & SPI_FLASH_CTRL_CLK_HI_MASK) <<
			SPI_FLASH_CTRL_CLK_HI_SHIFT |
		(CUSTOM_SPI_CLK_LO & SPI_FLASH_CTRL_CLK_LO_MASK) <<
			SPI_FLASH_CTRL_CLK_LO_SHIFT |
		(CUSTOM_SPI_CS_HOLD & SPI_FLASH_CTRL_CS_HOLD_MASK) <<
			SPI_FLASH_CTRL_CS_HOLD_SHIFT |
		(CUSTOM_SPI_CS_HI & SPI_FLASH_CTRL_CS_HI_MASK) <<
			SPI_FLASH_CTRL_CS_HI_SHIFT |
		(0x1 & SPI_FLASH_CTRL_INS_MASK) << SPI_FLASH_CTRL_INS_SHIFT;

	ATL2_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);

	value |= SPI_FLASH_CTRL_START;

	ATL2_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);

	for (i = 0; i < 10; i++) {
		msleep(1);
		value = ATL2_READ_REG(hw, REG_SPI_FLASH_CTRL);
		if (!(value & SPI_FLASH_CTRL_START))
			break;
	}

	if (value & SPI_FLASH_CTRL_START)
		return false;

	*buf = ATL2_READ_REG(hw, REG_SPI_DATA);

	return true;
}