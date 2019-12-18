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
struct dmfe_board_info {int cr6_data; int media_mode; int PHY_reg4; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  ioaddr; scalar_t__ chip_type; } ;

/* Variables and functions */
#define  DMFE_100MFD 131 
#define  DMFE_100MHF 130 
#define  DMFE_10MFD 129 
#define  DMFE_10MHF 128 
 int DMFE_AUTO ; 
 int /*<<< orphan*/  PCI_DM9009_ID ; 
 int /*<<< orphan*/  PCI_DM9102_ID ; 
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmfe_set_phyxcer(struct dmfe_board_info *db)
{
	u16 phy_reg;

	/* Select 10/100M phyxcer */
	db->cr6_data &= ~0x40000;
	update_cr6(db->cr6_data, db->ioaddr);

	/* DM9009 Chip: Phyxcer reg18 bit12=0 */
	if (db->chip_id == PCI_DM9009_ID) {
		phy_reg = phy_read(db->ioaddr,
				   db->phy_addr, 18, db->chip_id) & ~0x1000;

		phy_write(db->ioaddr,
			  db->phy_addr, 18, phy_reg, db->chip_id);
	}

	/* Phyxcer capability setting */
	phy_reg = phy_read(db->ioaddr, db->phy_addr, 4, db->chip_id) & ~0x01e0;

	if (db->media_mode & DMFE_AUTO) {
		/* AUTO Mode */
		phy_reg |= db->PHY_reg4;
	} else {
		/* Force Mode */
		switch(db->media_mode) {
		case DMFE_10MHF: phy_reg |= 0x20; break;
		case DMFE_10MFD: phy_reg |= 0x40; break;
		case DMFE_100MHF: phy_reg |= 0x80; break;
		case DMFE_100MFD: phy_reg |= 0x100; break;
		}
		if (db->chip_id == PCI_DM9009_ID) phy_reg &= 0x61;
	}

  	/* Write new capability to Phyxcer Reg4 */
	if ( !(phy_reg & 0x01e0)) {
		phy_reg|=db->PHY_reg4;
		db->media_mode|=DMFE_AUTO;
	}
	phy_write(db->ioaddr, db->phy_addr, 4, phy_reg, db->chip_id);

 	/* Restart Auto-Negotiation */
	if ( db->chip_type && (db->chip_id == PCI_DM9102_ID) )
		phy_write(db->ioaddr, db->phy_addr, 0, 0x1800, db->chip_id);
	if ( !db->chip_type )
		phy_write(db->ioaddr, db->phy_addr, 0, 0x1200, db->chip_id);
}