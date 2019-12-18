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
struct dmfe_board_info {int cr6_data; scalar_t__ chip_id; void* op_mode; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 void* DMFE_100MFD ; 
 void* DMFE_100MHF ; 
 void* DMFE_10MFD ; 
 void* DMFE_10MHF ; 
 int /*<<< orphan*/  DMFE_DBUG (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ PCI_DM9132_ID ; 
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 dmfe_sense_speed(struct dmfe_board_info * db)
{
	u8 ErrFlag = 0;
	u16 phy_mode;

	/* CR6 bit18=0, select 10/100M */
	update_cr6( (db->cr6_data & ~0x40000), db->ioaddr);

	phy_mode = phy_read(db->ioaddr, db->phy_addr, 1, db->chip_id);
	phy_mode = phy_read(db->ioaddr, db->phy_addr, 1, db->chip_id);

	if ( (phy_mode & 0x24) == 0x24 ) {
		if (db->chip_id == PCI_DM9132_ID)	/* DM9132 */
			phy_mode = phy_read(db->ioaddr,
				    db->phy_addr, 7, db->chip_id) & 0xf000;
		else 				/* DM9102/DM9102A */
			phy_mode = phy_read(db->ioaddr,
				    db->phy_addr, 17, db->chip_id) & 0xf000;
		/* printk(DRV_NAME ": Phy_mode %x ",phy_mode); */
		switch (phy_mode) {
		case 0x1000: db->op_mode = DMFE_10MHF; break;
		case 0x2000: db->op_mode = DMFE_10MFD; break;
		case 0x4000: db->op_mode = DMFE_100MHF; break;
		case 0x8000: db->op_mode = DMFE_100MFD; break;
		default: db->op_mode = DMFE_10MHF;
			ErrFlag = 1;
			break;
		}
	} else {
		db->op_mode = DMFE_10MHF;
		DMFE_DBUG(0, "Link Failed :", phy_mode);
		ErrFlag = 1;
	}

	return ErrFlag;
}