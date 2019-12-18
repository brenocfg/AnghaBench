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
typedef  int u16 ;
struct phytbl_info {int* tbl_ptr; int tbl_len; int tbl_width; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct cordic_iq {int i; int q; } ;
struct brcms_phy_lcnphy {scalar_t__ lcnphy_spurmod; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {int phy_tx_tone_freq; TYPE_1__ u; } ;
typedef  int s32 ;

/* Variables and functions */
 int FLOAT (int) ; 
 int /*<<< orphan*/  LCNPHY_TBL_ID_SAMPLEPLAY ; 
 int abs (int) ; 
 struct cordic_iq cordic_calc_iq (int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_deaf_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_run_samples (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_txrx_spur_avoidance_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void
wlc_lcnphy_start_tx_tone(struct brcms_phy *pi, s32 f_kHz, u16 max_val,
			 bool iqcalmode)
{
	u8 phy_bw;
	u16 num_samps, t, k;
	u32 bw;
	s32 theta = 0, rot = 0;
	struct cordic_iq tone_samp;
	u32 data_buf[64];
	u16 i_samp, q_samp;
	struct phytbl_info tab;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	pi->phy_tx_tone_freq = f_kHz;

	wlc_lcnphy_deaf_mode(pi, true);

	phy_bw = 40;
	if (pi_lcn->lcnphy_spurmod) {
		write_phy_reg(pi, 0x942, 0x2);
		write_phy_reg(pi, 0x93b, 0x0);
		write_phy_reg(pi, 0x93c, 0x0);
		wlc_lcnphy_txrx_spur_avoidance_mode(pi, false);
	}

	if (f_kHz) {
		k = 1;
		do {
			bw = phy_bw * 1000 * k;
			num_samps = bw / abs(f_kHz);
			k++;
		} while ((num_samps * (u32) (abs(f_kHz))) != bw);
	} else
		num_samps = 2;

	rot = ((f_kHz * 36) / phy_bw) / 100;
	theta = 0;

	for (t = 0; t < num_samps; t++) {

		tone_samp = cordic_calc_iq(theta);

		theta += rot;

		i_samp = (u16) (FLOAT(tone_samp.i * max_val) & 0x3ff);
		q_samp = (u16) (FLOAT(tone_samp.q * max_val) & 0x3ff);
		data_buf[t] = (i_samp << 10) | q_samp;
	}

	mod_phy_reg(pi, 0x6d6, (0x3 << 0), 0 << 0);

	mod_phy_reg(pi, 0x6da, (0x1 << 3), 1 << 3);

	tab.tbl_ptr = data_buf;
	tab.tbl_len = num_samps;
	tab.tbl_id = LCNPHY_TBL_ID_SAMPLEPLAY;
	tab.tbl_offset = 0;
	tab.tbl_width = 32;
	wlc_lcnphy_write_table(pi, &tab);

	wlc_lcnphy_run_samples(pi, num_samps, 0xffff, 0, iqcalmode);
}