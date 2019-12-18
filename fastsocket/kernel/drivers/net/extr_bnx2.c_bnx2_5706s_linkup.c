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
struct bnx2 {int link_up; void* duplex; int /*<<< orphan*/  mii_lpa; int /*<<< orphan*/  mii_adv; int /*<<< orphan*/  mii_bmcr; int /*<<< orphan*/  line_speed; } ;

/* Variables and functions */
 int ADVERTISE_1000XFULL ; 
 int ADVERTISE_1000XHALF ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  bnx2_read_phy (struct bnx2*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
bnx2_5706s_linkup(struct bnx2 *bp)
{
	u32 bmcr, local_adv, remote_adv, common;

	bp->link_up = 1;
	bp->line_speed = SPEED_1000;

	bnx2_read_phy(bp, bp->mii_bmcr, &bmcr);
	if (bmcr & BMCR_FULLDPLX) {
		bp->duplex = DUPLEX_FULL;
	}
	else {
		bp->duplex = DUPLEX_HALF;
	}

	if (!(bmcr & BMCR_ANENABLE)) {
		return 0;
	}

	bnx2_read_phy(bp, bp->mii_adv, &local_adv);
	bnx2_read_phy(bp, bp->mii_lpa, &remote_adv);

	common = local_adv & remote_adv;
	if (common & (ADVERTISE_1000XHALF | ADVERTISE_1000XFULL)) {

		if (common & ADVERTISE_1000XFULL) {
			bp->duplex = DUPLEX_FULL;
		}
		else {
			bp->duplex = DUPLEX_HALF;
		}
	}

	return 0;
}