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
typedef  scalar_t__ u32 ;
typedef  int u16 ;

/* Variables and functions */
 unsigned long DCR9 ; 
 scalar_t__ PCI_DM9132_ID ; 
 int /*<<< orphan*/  PHY_DATA_0 ; 
 int /*<<< orphan*/  PHY_DATA_1 ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 
 int /*<<< orphan*/  phy_write_1bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_write(unsigned long iobase, u8 phy_addr, u8 offset,
		      u16 phy_data, u32 chip_id)
{
	u16 i;
	unsigned long ioaddr;

	if (chip_id == PCI_DM9132_ID) {
		ioaddr = iobase + 0x80 + offset * 4;
		outw(phy_data, ioaddr);
	} else {
		/* DM9102/DM9102A Chip */
		ioaddr = iobase + DCR9;

		/* Send 33 synchronization clock to Phy controller */
		for (i = 0; i < 35; i++)
			phy_write_1bit(ioaddr, PHY_DATA_1);

		/* Send start command(01) to Phy */
		phy_write_1bit(ioaddr, PHY_DATA_0);
		phy_write_1bit(ioaddr, PHY_DATA_1);

		/* Send write command(01) to Phy */
		phy_write_1bit(ioaddr, PHY_DATA_0);
		phy_write_1bit(ioaddr, PHY_DATA_1);

		/* Send Phy address */
		for (i = 0x10; i > 0; i = i >> 1)
			phy_write_1bit(ioaddr,
				       phy_addr & i ? PHY_DATA_1 : PHY_DATA_0);

		/* Send register address */
		for (i = 0x10; i > 0; i = i >> 1)
			phy_write_1bit(ioaddr,
				       offset & i ? PHY_DATA_1 : PHY_DATA_0);

		/* written trasnition */
		phy_write_1bit(ioaddr, PHY_DATA_1);
		phy_write_1bit(ioaddr, PHY_DATA_0);

		/* Write a word data to PHY controller */
		for ( i = 0x8000; i > 0; i >>= 1)
			phy_write_1bit(ioaddr,
				       phy_data & i ? PHY_DATA_1 : PHY_DATA_0);
	}
}