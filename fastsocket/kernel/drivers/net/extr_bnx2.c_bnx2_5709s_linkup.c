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
struct bnx2 {int link_up; int autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  line_speed; int /*<<< orphan*/  req_duplex; int /*<<< orphan*/  req_line_speed; } ;

/* Variables and functions */
 int AUTONEG_SPEED ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_BNX2_BLK_ADDR ; 
 int /*<<< orphan*/  MII_BNX2_BLK_ADDR_COMBO_IEEEB0 ; 
 int /*<<< orphan*/  MII_BNX2_BLK_ADDR_GP_STATUS ; 
 int MII_BNX2_GP_TOP_AN_FD ; 
#define  MII_BNX2_GP_TOP_AN_SPEED_10 132 
#define  MII_BNX2_GP_TOP_AN_SPEED_100 131 
#define  MII_BNX2_GP_TOP_AN_SPEED_1G 130 
#define  MII_BNX2_GP_TOP_AN_SPEED_1GKV 129 
#define  MII_BNX2_GP_TOP_AN_SPEED_2_5G 128 
 int MII_BNX2_GP_TOP_AN_SPEED_MSK ; 
 int /*<<< orphan*/  MII_BNX2_GP_TOP_AN_STATUS1 ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2_write_phy (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_5709s_linkup(struct bnx2 *bp)
{
	u32 val, speed;

	bp->link_up = 1;

	bnx2_write_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_GP_STATUS);
	bnx2_read_phy(bp, MII_BNX2_GP_TOP_AN_STATUS1, &val);
	bnx2_write_phy(bp, MII_BNX2_BLK_ADDR, MII_BNX2_BLK_ADDR_COMBO_IEEEB0);

	if ((bp->autoneg & AUTONEG_SPEED) == 0) {
		bp->line_speed = bp->req_line_speed;
		bp->duplex = bp->req_duplex;
		return 0;
	}
	speed = val & MII_BNX2_GP_TOP_AN_SPEED_MSK;
	switch (speed) {
		case MII_BNX2_GP_TOP_AN_SPEED_10:
			bp->line_speed = SPEED_10;
			break;
		case MII_BNX2_GP_TOP_AN_SPEED_100:
			bp->line_speed = SPEED_100;
			break;
		case MII_BNX2_GP_TOP_AN_SPEED_1G:
		case MII_BNX2_GP_TOP_AN_SPEED_1GKV:
			bp->line_speed = SPEED_1000;
			break;
		case MII_BNX2_GP_TOP_AN_SPEED_2_5G:
			bp->line_speed = SPEED_2500;
			break;
	}
	if (val & MII_BNX2_GP_TOP_AN_FD)
		bp->duplex = DUPLEX_FULL;
	else
		bp->duplex = DUPLEX_HALF;
	return 0;
}