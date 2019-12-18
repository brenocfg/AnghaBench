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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_TBL_ID_RFSEQ ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static u16 wlc_phy_read_lpf_bw_ctl_nphy(struct brcms_phy *pi, u16 offset)
{
	u16 lpf_bw_ctl_val = 0;
	u16 rx2tx_lpf_rc_lut_offset = 0;

	if (offset == 0) {
		if (CHSPEC_IS40(pi->radio_chanspec))
			rx2tx_lpf_rc_lut_offset = 0x159;
		else
			rx2tx_lpf_rc_lut_offset = 0x154;
	} else {
		rx2tx_lpf_rc_lut_offset = offset;
	}
	wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_RFSEQ, 1,
				(u32) rx2tx_lpf_rc_lut_offset, 16,
				&lpf_bw_ctl_val);

	lpf_bw_ctl_val = lpf_bw_ctl_val & 0x7;

	return lpf_bw_ctl_val;
}