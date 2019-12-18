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
typedef  int u32 ;
struct phytbl_info {int* tbl_ptr; int tbl_len; int tbl_id; int tbl_offset; int tbl_width; } ;
struct brcms_phy_lcnphy {int lcnphy_ofdmgainidxtableoffset; int lcnphy_dsssgainidxtableoffset; int lcnphy_tr_R_gain_val; int lcnphy_tr_T_gain_val; int lcnphy_Med_Low_Gain_db; int lcnphy_Very_Low_Gain_db; int lcnphy_gain_idx_14_lowword; int lcnphy_gain_idx_14_hiword; scalar_t__ lcnphy_input_pwr_offset_db; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_1__ u; } ;
typedef  scalar_t__ s8 ;
typedef  int s16 ;

/* Variables and functions */
 int LCNPHY_TBL_ID_GAIN_IDX ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_read_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void wlc_lcnphy_agc_temp_init(struct brcms_phy *pi)
{
	s16 temp;
	struct phytbl_info tab;
	u32 tableBuffer[2];
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	temp = (s16) read_phy_reg(pi, 0x4df);
	pi_lcn->lcnphy_ofdmgainidxtableoffset = (temp & (0xff << 0)) >> 0;

	if (pi_lcn->lcnphy_ofdmgainidxtableoffset > 127)
		pi_lcn->lcnphy_ofdmgainidxtableoffset -= 256;

	pi_lcn->lcnphy_dsssgainidxtableoffset = (temp & (0xff << 8)) >> 8;

	if (pi_lcn->lcnphy_dsssgainidxtableoffset > 127)
		pi_lcn->lcnphy_dsssgainidxtableoffset -= 256;

	tab.tbl_ptr = tableBuffer;
	tab.tbl_len = 2;
	tab.tbl_id = 17;
	tab.tbl_offset = 59;
	tab.tbl_width = 32;
	wlc_lcnphy_read_table(pi, &tab);

	if (tableBuffer[0] > 63)
		tableBuffer[0] -= 128;
	pi_lcn->lcnphy_tr_R_gain_val = tableBuffer[0];

	if (tableBuffer[1] > 63)
		tableBuffer[1] -= 128;
	pi_lcn->lcnphy_tr_T_gain_val = tableBuffer[1];

	temp = (s16) (read_phy_reg(pi, 0x434) & (0xff << 0));
	if (temp > 127)
		temp -= 256;
	pi_lcn->lcnphy_input_pwr_offset_db = (s8) temp;

	pi_lcn->lcnphy_Med_Low_Gain_db =
		(read_phy_reg(pi, 0x424) & (0xff << 8)) >> 8;
	pi_lcn->lcnphy_Very_Low_Gain_db =
		(read_phy_reg(pi, 0x425) & (0xff << 0)) >> 0;

	tab.tbl_ptr = tableBuffer;
	tab.tbl_len = 2;
	tab.tbl_id = LCNPHY_TBL_ID_GAIN_IDX;
	tab.tbl_offset = 28;
	tab.tbl_width = 32;
	wlc_lcnphy_read_table(pi, &tab);

	pi_lcn->lcnphy_gain_idx_14_lowword = tableBuffer[0];
	pi_lcn->lcnphy_gain_idx_14_hiword = tableBuffer[1];

}