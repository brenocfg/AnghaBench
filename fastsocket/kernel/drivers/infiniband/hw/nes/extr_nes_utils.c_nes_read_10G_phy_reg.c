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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_PHY ; 
 int /*<<< orphan*/  NES_IDX_MAC_INT_STATUS ; 
 int /*<<< orphan*/  NES_IDX_MAC_MDIO_CONTROL ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int) ; 
 int nes_read_indexed (struct nes_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void nes_read_10G_phy_reg(struct nes_device *nesdev, u8 phy_addr, u8 dev_addr, u16 phy_reg)
{
	u32 port_addr;
	u32 u32temp;
	u32 counter;

	port_addr = phy_addr;

	/* set address */
	nes_write_indexed(nesdev, NES_IDX_MAC_MDIO_CONTROL,
			0x00020000 | (u32)phy_reg | (((u32)dev_addr) << 18) | (((u32)port_addr) << 23));
	for (counter = 0; counter < 100 ; counter++) {
		udelay(30);
		u32temp = nes_read_indexed(nesdev, NES_IDX_MAC_INT_STATUS);
		if (u32temp & 1) {
			nes_write_indexed(nesdev, NES_IDX_MAC_INT_STATUS, 1);
			break;
		}
	}
	if (!(u32temp & 1))
		nes_debug(NES_DBG_PHY, "Phy is not responding. interrupt status = 0x%X.\n",
				u32temp);

	/* issue read */
	nes_write_indexed(nesdev, NES_IDX_MAC_MDIO_CONTROL,
			0x30020000 | (((u32)dev_addr) << 18) | (((u32)port_addr) << 23));
	for (counter = 0; counter < 100 ; counter++) {
		udelay(30);
		u32temp = nes_read_indexed(nesdev, NES_IDX_MAC_INT_STATUS);
		if (u32temp & 1) {
			nes_write_indexed(nesdev, NES_IDX_MAC_INT_STATUS, 1);
			break;
		}
	}
	if (!(u32temp & 1))
		nes_debug(NES_DBG_PHY, "Phy is not responding. interrupt status = 0x%X.\n",
				u32temp);
}