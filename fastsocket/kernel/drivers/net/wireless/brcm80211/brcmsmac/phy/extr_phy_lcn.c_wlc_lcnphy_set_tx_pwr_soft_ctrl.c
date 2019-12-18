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
typedef  int u16 ;
struct phytbl_info {int tbl_width; int tbl_len; int* tbl_ptr; int tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct brcms_phy {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 int LCNPHY_TX_PWR_CTRL_RATE_OFFSET ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 scalar_t__ wlc_lcnphy_tssi_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void wlc_lcnphy_set_tx_pwr_soft_ctrl(struct brcms_phy *pi, s8 index)
{
	u32 cck_offset[4] = { 22, 22, 22, 22 };
	u32 ofdm_offset, reg_offset_cck;
	int i;
	u16 index2;
	struct phytbl_info tab;

	if (wlc_lcnphy_tssi_based_pwr_ctrl_enabled(pi))
		return;

	mod_phy_reg(pi, 0x4a4, (0x1 << 14), (0x1) << 14);

	mod_phy_reg(pi, 0x4a4, (0x1 << 14), (0x0) << 14);

	or_phy_reg(pi, 0x6da, 0x0040);

	reg_offset_cck = 0;
	for (i = 0; i < 4; i++)
		cck_offset[i] -= reg_offset_cck;
	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_len = 4;
	tab.tbl_ptr = cck_offset;
	tab.tbl_offset = LCNPHY_TX_PWR_CTRL_RATE_OFFSET;
	wlc_lcnphy_write_table(pi, &tab);
	ofdm_offset = 0;
	tab.tbl_len = 1;
	tab.tbl_ptr = &ofdm_offset;
	for (i = 836; i < 862; i++) {
		tab.tbl_offset = i;
		wlc_lcnphy_write_table(pi, &tab);
	}

	mod_phy_reg(pi, 0x4a4, (0x1 << 15), (0x1) << 15);

	mod_phy_reg(pi, 0x4a4, (0x1 << 14), (0x1) << 14);

	mod_phy_reg(pi, 0x4a4, (0x1 << 13), (0x1) << 13);

	mod_phy_reg(pi, 0x4b0, (0x1 << 7), (0) << 7);

	mod_phy_reg(pi, 0x43b, (0x1 << 6), (0) << 6);

	mod_phy_reg(pi, 0x4a9, (0x1 << 15), (1) << 15);

	index2 = (u16) (index * 2);
	mod_phy_reg(pi, 0x4a9, (0x1ff << 0), (index2) << 0);

	mod_phy_reg(pi, 0x6a3, (0x1 << 4), (0) << 4);

}