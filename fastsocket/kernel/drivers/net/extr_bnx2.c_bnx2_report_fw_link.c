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
struct bnx2 {int phy_flags; int line_speed; int /*<<< orphan*/  mii_bmsr; scalar_t__ autoneg; int /*<<< orphan*/  duplex; scalar_t__ link_up; } ;

/* Variables and functions */
 int BMSR_ANEGCOMPLETE ; 
 int /*<<< orphan*/  BNX2_LINK_STATUS ; 
 int BNX2_LINK_STATUS_1000FULL ; 
 int BNX2_LINK_STATUS_1000HALF ; 
 int BNX2_LINK_STATUS_100FULL ; 
 int BNX2_LINK_STATUS_100HALF ; 
 int BNX2_LINK_STATUS_10FULL ; 
 int BNX2_LINK_STATUS_10HALF ; 
 int BNX2_LINK_STATUS_2500FULL ; 
 int BNX2_LINK_STATUS_2500HALF ; 
 int BNX2_LINK_STATUS_AN_COMPLETE ; 
 int BNX2_LINK_STATUS_AN_ENABLED ; 
 int BNX2_LINK_STATUS_LINK_DOWN ; 
 int BNX2_LINK_STATUS_LINK_UP ; 
 int BNX2_LINK_STATUS_PARALLEL_DET ; 
 int BNX2_PHY_FLAG_PARALLEL_DETECT ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2_shmem_wr (struct bnx2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bnx2_report_fw_link(struct bnx2 *bp)
{
	u32 fw_link_status = 0;

	if (bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP)
		return;

	if (bp->link_up) {
		u32 bmsr;

		switch (bp->line_speed) {
		case SPEED_10:
			if (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_10HALF;
			else
				fw_link_status = BNX2_LINK_STATUS_10FULL;
			break;
		case SPEED_100:
			if (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_100HALF;
			else
				fw_link_status = BNX2_LINK_STATUS_100FULL;
			break;
		case SPEED_1000:
			if (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_1000HALF;
			else
				fw_link_status = BNX2_LINK_STATUS_1000FULL;
			break;
		case SPEED_2500:
			if (bp->duplex == DUPLEX_HALF)
				fw_link_status = BNX2_LINK_STATUS_2500HALF;
			else
				fw_link_status = BNX2_LINK_STATUS_2500FULL;
			break;
		}

		fw_link_status |= BNX2_LINK_STATUS_LINK_UP;

		if (bp->autoneg) {
			fw_link_status |= BNX2_LINK_STATUS_AN_ENABLED;

			bnx2_read_phy(bp, bp->mii_bmsr, &bmsr);
			bnx2_read_phy(bp, bp->mii_bmsr, &bmsr);

			if (!(bmsr & BMSR_ANEGCOMPLETE) ||
			    bp->phy_flags & BNX2_PHY_FLAG_PARALLEL_DETECT)
				fw_link_status |= BNX2_LINK_STATUS_PARALLEL_DET;
			else
				fw_link_status |= BNX2_LINK_STATUS_AN_COMPLETE;
		}
	}
	else
		fw_link_status = BNX2_LINK_STATUS_LINK_DOWN;

	bnx2_shmem_wr(bp, BNX2_LINK_STATUS, fw_link_status);
}