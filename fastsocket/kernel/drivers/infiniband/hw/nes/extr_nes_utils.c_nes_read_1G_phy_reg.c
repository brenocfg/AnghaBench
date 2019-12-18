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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_PHY ; 
 int /*<<< orphan*/  NES_IDX_MAC_INT_STATUS ; 
 int /*<<< orphan*/  NES_IDX_MAC_MDIO_CONTROL ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int) ; 
 int nes_read_indexed (struct nes_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void nes_read_1G_phy_reg(struct nes_device *nesdev, u8 phy_reg, u8 phy_addr, u16 *data)
{
	u32 u32temp;
	u32 counter;

	/* nes_debug(NES_DBG_PHY, "phy addr = %d, mac_index = %d\n",
			phy_addr, nesdev->mac_index); */

	nes_write_indexed(nesdev, NES_IDX_MAC_MDIO_CONTROL,
			0x60020000 | ((u32)phy_reg << 18) | ((u32)phy_addr << 23));
	for (counter = 0; counter < 100 ; counter++) {
		udelay(30);
		u32temp = nes_read_indexed(nesdev, NES_IDX_MAC_INT_STATUS);
		if (u32temp & 1) {
			/* nes_debug(NES_DBG_PHY, "Phy interrupt status = 0x%X.\n", u32temp); */
			nes_write_indexed(nesdev, NES_IDX_MAC_INT_STATUS, 1);
			break;
		}
	}
	if (!(u32temp & 1)) {
		nes_debug(NES_DBG_PHY, "Phy is not responding. interrupt status = 0x%X.\n",
				u32temp);
		*data = 0xffff;
	} else {
		*data = (u16)nes_read_indexed(nesdev, NES_IDX_MAC_MDIO_CONTROL);
	}
}