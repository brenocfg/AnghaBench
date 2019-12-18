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
struct atl1_hw {scalar_t__ hw_addr; } ;

/* Variables and functions */
 int CUSTOM_SPI_CLK_HI ; 
 int CUSTOM_SPI_CLK_LO ; 
 int CUSTOM_SPI_CS_HI ; 
 int CUSTOM_SPI_CS_HOLD ; 
 int CUSTOM_SPI_CS_SETUP ; 
 scalar_t__ REG_SPI_ADDR ; 
 scalar_t__ REG_SPI_DATA ; 
 scalar_t__ REG_SPI_FLASH_CTRL ; 
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
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static bool atl1_spi_read(struct atl1_hw *hw, u32 addr, u32 *buf)
{
	int i;
	u32 value;

	iowrite32(0, hw->hw_addr + REG_SPI_DATA);
	iowrite32(addr, hw->hw_addr + REG_SPI_ADDR);

	value = SPI_FLASH_CTRL_WAIT_READY |
	    (CUSTOM_SPI_CS_SETUP & SPI_FLASH_CTRL_CS_SETUP_MASK) <<
	    SPI_FLASH_CTRL_CS_SETUP_SHIFT | (CUSTOM_SPI_CLK_HI &
					     SPI_FLASH_CTRL_CLK_HI_MASK) <<
	    SPI_FLASH_CTRL_CLK_HI_SHIFT | (CUSTOM_SPI_CLK_LO &
					   SPI_FLASH_CTRL_CLK_LO_MASK) <<
	    SPI_FLASH_CTRL_CLK_LO_SHIFT | (CUSTOM_SPI_CS_HOLD &
					   SPI_FLASH_CTRL_CS_HOLD_MASK) <<
	    SPI_FLASH_CTRL_CS_HOLD_SHIFT | (CUSTOM_SPI_CS_HI &
					    SPI_FLASH_CTRL_CS_HI_MASK) <<
	    SPI_FLASH_CTRL_CS_HI_SHIFT | (1 & SPI_FLASH_CTRL_INS_MASK) <<
	    SPI_FLASH_CTRL_INS_SHIFT;

	iowrite32(value, hw->hw_addr + REG_SPI_FLASH_CTRL);

	value |= SPI_FLASH_CTRL_START;
	iowrite32(value, hw->hw_addr + REG_SPI_FLASH_CTRL);
	ioread32(hw->hw_addr + REG_SPI_FLASH_CTRL);

	for (i = 0; i < 10; i++) {
		msleep(1);
		value = ioread32(hw->hw_addr + REG_SPI_FLASH_CTRL);
		if (!(value & SPI_FLASH_CTRL_START))
			break;
	}

	if (value & SPI_FLASH_CTRL_START)
		return false;

	*buf = ioread32(hw->hw_addr + REG_SPI_DATA);

	return true;
}