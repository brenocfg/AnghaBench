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
struct dmfe_board_info {char* srom; int cr15_data; int NIC_capability; int PHY_reg4; int HPNA_command; int HPNA_present; int cr6_data; int HPNA_timer; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  ioaddr; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int CR15_DEFAULT ; 
 int /*<<< orphan*/  DMFE_100MFD ; 
 int /*<<< orphan*/  DMFE_100MHF ; 
 int /*<<< orphan*/  DMFE_10MFD ; 
 int /*<<< orphan*/  DMFE_1M_HPNA ; 
 int /*<<< orphan*/  DMFE_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int HPNA_mode ; 
 scalar_t__ HPNA_rx_cmd ; 
 int HPNA_tx_cmd ; 
 int SF_mode ; 
 int SROM_V41_CODE ; 
 int /*<<< orphan*/  dmfe_media_mode ; 
 int /*<<< orphan*/  dmfe_program_DM9801 (struct dmfe_board_info*,int) ; 
 int /*<<< orphan*/  dmfe_program_DM9802 (struct dmfe_board_info*) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int le32_to_cpup (int /*<<< orphan*/ *) ; 
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cr6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmfe_parse_srom(struct dmfe_board_info * db)
{
	char * srom = db->srom;
	int dmfe_mode, tmp_reg;

	DMFE_DBUG(0, "dmfe_parse_srom() ", 0);

	/* Init CR15 */
	db->cr15_data = CR15_DEFAULT;

	/* Check SROM Version */
	if ( ( (int) srom[18] & 0xff) == SROM_V41_CODE) {
		/* SROM V4.01 */
		/* Get NIC support media mode */
		db->NIC_capability = le16_to_cpup((__le16 *) (srom + 34));
		db->PHY_reg4 = 0;
		for (tmp_reg = 1; tmp_reg < 0x10; tmp_reg <<= 1) {
			switch( db->NIC_capability & tmp_reg ) {
			case 0x1: db->PHY_reg4 |= 0x0020; break;
			case 0x2: db->PHY_reg4 |= 0x0040; break;
			case 0x4: db->PHY_reg4 |= 0x0080; break;
			case 0x8: db->PHY_reg4 |= 0x0100; break;
			}
		}

		/* Media Mode Force or not check */
		dmfe_mode = (le32_to_cpup((__le32 *) (srom + 34)) &
			     le32_to_cpup((__le32 *) (srom + 36)));
		switch(dmfe_mode) {
		case 0x4: dmfe_media_mode = DMFE_100MHF; break;	/* 100MHF */
		case 0x2: dmfe_media_mode = DMFE_10MFD; break;	/* 10MFD */
		case 0x8: dmfe_media_mode = DMFE_100MFD; break;	/* 100MFD */
		case 0x100:
		case 0x200: dmfe_media_mode = DMFE_1M_HPNA; break;/* HomePNA */
		}

		/* Special Function setting */
		/* VLAN function */
		if ( (SF_mode & 0x1) || (srom[43] & 0x80) )
			db->cr15_data |= 0x40;

		/* Flow Control */
		if ( (SF_mode & 0x2) || (srom[40] & 0x1) )
			db->cr15_data |= 0x400;

		/* TX pause packet */
		if ( (SF_mode & 0x4) || (srom[40] & 0xe) )
			db->cr15_data |= 0x9800;
	}

	/* Parse HPNA parameter */
	db->HPNA_command = 1;

	/* Accept remote command or not */
	if (HPNA_rx_cmd == 0)
		db->HPNA_command |= 0x8000;

	 /* Issue remote command & operation mode */
	if (HPNA_tx_cmd == 1)
		switch(HPNA_mode) {	/* Issue Remote Command */
		case 0: db->HPNA_command |= 0x0904; break;
		case 1: db->HPNA_command |= 0x0a00; break;
		case 2: db->HPNA_command |= 0x0506; break;
		case 3: db->HPNA_command |= 0x0602; break;
		}
	else
		switch(HPNA_mode) {	/* Don't Issue */
		case 0: db->HPNA_command |= 0x0004; break;
		case 1: db->HPNA_command |= 0x0000; break;
		case 2: db->HPNA_command |= 0x0006; break;
		case 3: db->HPNA_command |= 0x0002; break;
		}

	/* Check DM9801 or DM9802 present or not */
	db->HPNA_present = 0;
	update_cr6(db->cr6_data|0x40000, db->ioaddr);
	tmp_reg = phy_read(db->ioaddr, db->phy_addr, 3, db->chip_id);
	if ( ( tmp_reg & 0xfff0 ) == 0xb900 ) {
		/* DM9801 or DM9802 present */
		db->HPNA_timer = 8;
		if ( phy_read(db->ioaddr, db->phy_addr, 31, db->chip_id) == 0x4404) {
			/* DM9801 HomeRun */
			db->HPNA_present = 1;
			dmfe_program_DM9801(db, tmp_reg);
		} else {
			/* DM9802 LongRun */
			db->HPNA_present = 2;
			dmfe_program_DM9802(db);
		}
	}

}