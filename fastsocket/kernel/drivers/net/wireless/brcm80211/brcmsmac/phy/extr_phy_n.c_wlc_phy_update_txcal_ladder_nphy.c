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
typedef  scalar_t__ u16 ;
struct nphy_txiqcal_ladder {int member_0; int member_1; scalar_t__ percent; int g_env; } ;
struct brcms_phy {int nphy_txcal_bbmult; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPHY_TBL_ID_IQLOCAL ; 
 scalar_t__ PHY_CORE_0 ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,scalar_t__*) ; 

__attribute__((used)) static void wlc_phy_update_txcal_ladder_nphy(struct brcms_phy *pi, u16 core)
{
	int index;
	u32 bbmult_scale;
	u16 bbmult;
	u16 tblentry;

	struct nphy_txiqcal_ladder ladder_lo[] = {
		{3, 0}, {4, 0}, {6, 0}, {9, 0}, {13, 0}, {18, 0},
		{25, 0}, {25, 1}, {25, 2}, {25, 3}, {25, 4}, {25, 5},
		{25, 6}, {25, 7}, {35, 7}, {50, 7}, {71, 7}, {100, 7}
	};

	struct nphy_txiqcal_ladder ladder_iq[] = {
		{3, 0}, {4, 0}, {6, 0}, {9, 0}, {13, 0}, {18, 0},
		{25, 0}, {35, 0}, {50, 0}, {71, 0}, {100, 0}, {100, 1},
		{100, 2}, {100, 3}, {100, 4}, {100, 5}, {100, 6}, {100, 7}
	};

	bbmult = (core == PHY_CORE_0) ?
		 ((pi->nphy_txcal_bbmult >> 8) & 0xff) :
		 (pi->nphy_txcal_bbmult & 0xff);

	for (index = 0; index < 18; index++) {
		bbmult_scale = ladder_lo[index].percent * bbmult;
		bbmult_scale /= 100;

		tblentry =
			((bbmult_scale & 0xff) << 8) | ladder_lo[index].g_env;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 1, index, 16,
					 &tblentry);

		bbmult_scale = ladder_iq[index].percent * bbmult;
		bbmult_scale /= 100;

		tblentry =
			((bbmult_scale & 0xff) << 8) | ladder_iq[index].g_env;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 1, index + 32,
					 16, &tblentry);
	}
}