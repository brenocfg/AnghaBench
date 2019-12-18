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
typedef  int u16 ;
struct dmfe_board_info {int op_mode; int cr6_data; int media_mode; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  ioaddr; scalar_t__ chip_type; } ;

/* Variables and functions */
 int CR6_FDM ; 
#define  DMFE_100MFD 131 
#define  DMFE_100MHF 130 
#define  DMFE_10MFD 129 
#define  DMFE_10MHF 128 
 int /*<<< orphan*/  PCI_DM9102_ID ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmfe_process_mode(struct dmfe_board_info *db)
{
	u16 phy_reg;

	/* Full Duplex Mode Check */
	if (db->op_mode & 0x4)
		db->cr6_data |= CR6_FDM;	/* Set Full Duplex Bit */
	else
		db->cr6_data &= ~CR6_FDM;	/* Clear Full Duplex Bit */

	/* Transciver Selection */
	if (db->op_mode & 0x10)		/* 1M HomePNA */
		db->cr6_data |= 0x40000;/* External MII select */
	else
		db->cr6_data &= ~0x40000;/* Internal 10/100 transciver */

	update_cr6(db->cr6_data, db->ioaddr);

	/* 10/100M phyxcer force mode need */
	if ( !(db->media_mode & 0x18)) {
		/* Forece Mode */
		phy_reg = phy_read(db->ioaddr, db->phy_addr, 6, db->chip_id);
		if ( !(phy_reg & 0x1) ) {
			/* parter without N-Way capability */
			phy_reg = 0x0;
			switch(db->op_mode) {
			case DMFE_10MHF: phy_reg = 0x0; break;
			case DMFE_10MFD: phy_reg = 0x100; break;
			case DMFE_100MHF: phy_reg = 0x2000; break;
			case DMFE_100MFD: phy_reg = 0x2100; break;
			}
			phy_write(db->ioaddr,
				  db->phy_addr, 0, phy_reg, db->chip_id);
       			if ( db->chip_type && (db->chip_id == PCI_DM9102_ID) )
				mdelay(20);
			phy_write(db->ioaddr,
				  db->phy_addr, 0, phy_reg, db->chip_id);
		}
	}
}