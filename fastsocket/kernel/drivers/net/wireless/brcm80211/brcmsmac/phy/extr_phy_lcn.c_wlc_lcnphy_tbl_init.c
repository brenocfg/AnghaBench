#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  struct phytbl_info {int tbl_width; int* tbl_ptr; int tbl_len; int tbl_offset; void* tbl_id; } const phytbl_info ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_2__* sh; int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;
struct TYPE_4__ {int boardflags; int boardrev; } ;

/* Variables and functions */
 int BFL_EXTLNA ; 
 int BFL_EXTLNA_5GHz ; 
 int BFL_FEM ; 
 int BFL_FEM_BT ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 void* LCNPHY_TBL_ID_RFSEQ ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 struct phytbl_info const dot11lcn_sw_ctrl_tbl_info_4313 ; 
 struct phytbl_info const dot11lcn_sw_ctrl_tbl_info_4313_bt_epa ; 
 struct phytbl_info const dot11lcn_sw_ctrl_tbl_info_4313_bt_epa_p250 ; 
 struct phytbl_info const dot11lcn_sw_ctrl_tbl_info_4313_epa ; 
 int /*<<< orphan*/  dot11lcnphy_2GHz_extPA_gaintable_rev0 ; 
 int /*<<< orphan*/  dot11lcnphy_2GHz_gaintable_rev0 ; 
 struct phytbl_info const* dot11lcnphytbl_info_rev0 ; 
 size_t dot11lcnphytbl_info_sz_rev0 ; 
 struct phytbl_info const* dot11lcnphytbl_rx_gain_info_2G_rev2 ; 
 int dot11lcnphytbl_rx_gain_info_2G_rev2_sz ; 
 struct phytbl_info const* dot11lcnphytbl_rx_gain_info_5G_rev2 ; 
 int dot11lcnphytbl_rx_gain_info_5G_rev2_sz ; 
 struct phytbl_info const* dot11lcnphytbl_rx_gain_info_extlna_2G_rev2 ; 
 struct phytbl_info const* dot11lcnphytbl_rx_gain_info_extlna_5G_rev2 ; 
 int /*<<< orphan*/  wlc_lcnphy_clear_papd_comptable (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_load_rfpower (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_load_tx_gain_table (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info const*) ; 

__attribute__((used)) static void wlc_lcnphy_tbl_init(struct brcms_phy *pi)
{
	uint idx;
	u8 phybw40;
	struct phytbl_info tab;
	u32 val;

	phybw40 = CHSPEC_IS40(pi->radio_chanspec);

	for (idx = 0; idx < dot11lcnphytbl_info_sz_rev0; idx++)
		wlc_lcnphy_write_table(pi, &dot11lcnphytbl_info_rev0[idx]);

	if (pi->sh->boardflags & BFL_FEM_BT) {
		tab.tbl_id = LCNPHY_TBL_ID_RFSEQ;
		tab.tbl_width = 16;
		tab.tbl_ptr = &val;
		tab.tbl_len = 1;
		val = 100;
		tab.tbl_offset = 4;
		wlc_lcnphy_write_table(pi, &tab);
	}

	tab.tbl_id = LCNPHY_TBL_ID_RFSEQ;
	tab.tbl_width = 16;
	tab.tbl_ptr = &val;
	tab.tbl_len = 1;

	val = 114;
	tab.tbl_offset = 0;
	wlc_lcnphy_write_table(pi, &tab);

	val = 130;
	tab.tbl_offset = 1;
	wlc_lcnphy_write_table(pi, &tab);

	val = 6;
	tab.tbl_offset = 8;
	wlc_lcnphy_write_table(pi, &tab);

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (pi->sh->boardflags & BFL_FEM)
			wlc_lcnphy_load_tx_gain_table(
				pi,
				dot11lcnphy_2GHz_extPA_gaintable_rev0);
		else
			wlc_lcnphy_load_tx_gain_table(
				pi,
				dot11lcnphy_2GHz_gaintable_rev0);
	}

	if (LCNREV_IS(pi->pubpi.phy_rev, 2)) {
		const struct phytbl_info *tb;
		int l;

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			l = dot11lcnphytbl_rx_gain_info_2G_rev2_sz;
			if (pi->sh->boardflags & BFL_EXTLNA)
				tb = dot11lcnphytbl_rx_gain_info_extlna_2G_rev2;
			else
				tb = dot11lcnphytbl_rx_gain_info_2G_rev2;
		} else {
			l = dot11lcnphytbl_rx_gain_info_5G_rev2_sz;
			if (pi->sh->boardflags & BFL_EXTLNA_5GHz)
				tb = dot11lcnphytbl_rx_gain_info_extlna_5G_rev2;
			else
				tb = dot11lcnphytbl_rx_gain_info_5G_rev2;
		}

		for (idx = 0; idx < l; idx++)
			wlc_lcnphy_write_table(pi, &tb[idx]);
	}

	if ((pi->sh->boardflags & BFL_FEM)
	    && !(pi->sh->boardflags & BFL_FEM_BT))
		wlc_lcnphy_write_table(pi, &dot11lcn_sw_ctrl_tbl_info_4313_epa);
	else if (pi->sh->boardflags & BFL_FEM_BT) {
		if (pi->sh->boardrev < 0x1250)
			wlc_lcnphy_write_table(
				pi,
				&dot11lcn_sw_ctrl_tbl_info_4313_bt_epa);
		else
			wlc_lcnphy_write_table(
				pi,
				&dot11lcn_sw_ctrl_tbl_info_4313_bt_epa_p250);
	} else
		wlc_lcnphy_write_table(pi, &dot11lcn_sw_ctrl_tbl_info_4313);

	wlc_lcnphy_load_rfpower(pi);

	wlc_lcnphy_clear_papd_comptable(pi);
}