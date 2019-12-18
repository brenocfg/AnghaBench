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
typedef  int u16 ;
struct uli526x_board_info {void* op_mode; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 void* ULI526X_100MFD ; 
 void* ULI526X_100MHF ; 
 void* ULI526X_10MFD ; 
 void* ULI526X_10MHF ; 
 int /*<<< orphan*/  ULI526X_DBUG (int /*<<< orphan*/ ,char*,int) ; 
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 uli526x_sense_speed(struct uli526x_board_info * db)
{
	u8 ErrFlag = 0;
	u16 phy_mode;

	phy_mode = phy_read(db->ioaddr, db->phy_addr, 1, db->chip_id);
	phy_mode = phy_read(db->ioaddr, db->phy_addr, 1, db->chip_id);

	if ( (phy_mode & 0x24) == 0x24 ) {

		phy_mode = ((phy_read(db->ioaddr, db->phy_addr, 5, db->chip_id) & 0x01e0)<<7);
		if(phy_mode&0x8000)
			phy_mode = 0x8000;
		else if(phy_mode&0x4000)
			phy_mode = 0x4000;
		else if(phy_mode&0x2000)
			phy_mode = 0x2000;
		else
			phy_mode = 0x1000;

		/* printk(DRV_NAME ": Phy_mode %x ",phy_mode); */
		switch (phy_mode) {
		case 0x1000: db->op_mode = ULI526X_10MHF; break;
		case 0x2000: db->op_mode = ULI526X_10MFD; break;
		case 0x4000: db->op_mode = ULI526X_100MHF; break;
		case 0x8000: db->op_mode = ULI526X_100MFD; break;
		default: db->op_mode = ULI526X_10MHF; ErrFlag = 1; break;
		}
	} else {
		db->op_mode = ULI526X_10MHF;
		ULI526X_DBUG(0, "Link Failed :", phy_mode);
		ErrFlag = 1;
	}

	return ErrFlag;
}