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
typedef  int uint ;
struct dmfe_board_info {int HPNA_command; int HPNA_timer; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 int phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmfe_HPNA_remote_cmd_chk(struct dmfe_board_info * db)
{
	uint phy_reg;

	/* Got remote device status */
	phy_reg = phy_read(db->ioaddr, db->phy_addr, 17, db->chip_id) & 0x60;
	switch(phy_reg) {
	case 0x00: phy_reg = 0x0a00;break; /* LP/LS */
	case 0x20: phy_reg = 0x0900;break; /* LP/HS */
	case 0x40: phy_reg = 0x0600;break; /* HP/LS */
	case 0x60: phy_reg = 0x0500;break; /* HP/HS */
	}

	/* Check remote device status match our setting ot not */
	if ( phy_reg != (db->HPNA_command & 0x0f00) ) {
		phy_write(db->ioaddr, db->phy_addr, 16, db->HPNA_command,
			  db->chip_id);
		db->HPNA_timer=8;
	} else
		db->HPNA_timer=600;	/* Match, every 10 minutes, check */
}