#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ phyhang_avoid; TYPE_1__ pubpi; } ;

/* Variables and functions */
 int NPHY_REV3_RFSEQ_CMD_END ; 
 int NPHY_RFSEQ_CMD_END ; 
 int /*<<< orphan*/  NPHY_TBL_ID_RFSEQ ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 

__attribute__((used)) static void
wlc_phy_set_rfseq_nphy(struct brcms_phy *pi, u8 cmd, u8 *events, u8 *dlys,
		       u8 len)
{
	u32 t1_offset, t2_offset;
	u8 ctr;
	u8 end_event =
		NREV_GE(pi->pubpi.phy_rev,
			3) ? NPHY_REV3_RFSEQ_CMD_END : NPHY_RFSEQ_CMD_END;
	u8 end_dly = 1;

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	t1_offset = cmd << 4;
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, len, t1_offset, 8,
				 events);
	t2_offset = t1_offset + 0x080;
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, len, t2_offset, 8,
				 dlys);

	for (ctr = len; ctr < 16; ctr++) {
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, 1,
					 t1_offset + ctr, 8, &end_event);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_RFSEQ, 1,
					 t2_offset + ctr, 8, &end_dly);
	}

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
}