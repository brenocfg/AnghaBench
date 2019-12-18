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
struct lcnphy_unsign16_struct {int re; int im; } ;
struct lcnphy_spb_tone {int re; int im; } ;
struct brcms_phy {int dummy; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RADIO_2064_REG026 ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct lcnphy_spb_tone* lcnphy_spb_tone_3750 ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int read_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 struct lcnphy_unsign16_struct wlc_lcnphy_get_cc (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_samp_cap (struct brcms_phy*,int,int,int*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_cc (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_start_tx_tone (struct brcms_phy*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_stop_tx_tone (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_iqlo_loopback (struct brcms_phy*,int*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_iqlo_loopback_cleanup (struct brcms_phy*,int*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wlc_lcnphy_a1(struct brcms_phy *pi, int cal_type, int num_levels,
	      int step_size_lg2)
{
	const struct lcnphy_spb_tone *phy_c1;
	struct lcnphy_spb_tone phy_c2;
	struct lcnphy_unsign16_struct phy_c3;
	int phy_c4, phy_c5, k, l, j, phy_c6;
	u16 phy_c7, phy_c8, phy_c9;
	s16 phy_c10, phy_c11, phy_c12, phy_c13, phy_c14, phy_c15, phy_c16;
	s16 *ptr, phy_c17;
	s32 phy_c18, phy_c19;
	u32 phy_c20, phy_c21;
	bool phy_c22, phy_c23, phy_c24, phy_c25;
	u16 phy_c26, phy_c27;
	u16 phy_c28, phy_c29, phy_c30;
	u16 phy_c31;
	u16 *phy_c32;
	phy_c21 = 0;
	phy_c10 = phy_c13 = phy_c14 = phy_c8 = 0;
	ptr = kmalloc(sizeof(s16) * 131, GFP_ATOMIC);
	if (NULL == ptr)
		return;

	phy_c32 = kmalloc(sizeof(u16) * 20, GFP_ATOMIC);
	if (NULL == phy_c32) {
		kfree(ptr);
		return;
	}
	phy_c26 = read_phy_reg(pi, 0x6da);
	phy_c27 = read_phy_reg(pi, 0x6db);
	phy_c31 = read_radio_reg(pi, RADIO_2064_REG026);
	write_phy_reg(pi, 0x93d, 0xC0);

	wlc_lcnphy_start_tx_tone(pi, 3750, 88, 0);
	write_phy_reg(pi, 0x6da, 0xffff);
	or_phy_reg(pi, 0x6db, 0x3);

	wlc_lcnphy_tx_iqlo_loopback(pi, phy_c32);
	udelay(500);
	phy_c28 = read_phy_reg(pi, 0x938);
	phy_c29 = read_phy_reg(pi, 0x4d7);
	phy_c30 = read_phy_reg(pi, 0x4d8);
	or_phy_reg(pi, 0x938, 0x1 << 2);
	or_phy_reg(pi, 0x4d7, 0x1 << 2);
	or_phy_reg(pi, 0x4d7, 0x1 << 3);
	mod_phy_reg(pi, 0x4d7, (0x7 << 12), 0x2 << 12);
	or_phy_reg(pi, 0x4d8, 1 << 0);
	or_phy_reg(pi, 0x4d8, 1 << 1);
	mod_phy_reg(pi, 0x4d8, (0x3ff << 2), 0x23A << 2);
	mod_phy_reg(pi, 0x4d8, (0x7 << 12), 0x7 << 12);
	phy_c1 = &lcnphy_spb_tone_3750[0];
	phy_c4 = 32;

	if (num_levels == 0) {
		if (cal_type != 0)
			num_levels = 4;
		else
			num_levels = 9;
	}
	if (step_size_lg2 == 0) {
		if (cal_type != 0)
			step_size_lg2 = 3;
		else
			step_size_lg2 = 8;
	}

	phy_c7 = (1 << step_size_lg2);
	phy_c3 = wlc_lcnphy_get_cc(pi, cal_type);
	phy_c15 = (s16) phy_c3.re;
	phy_c16 = (s16) phy_c3.im;
	if (cal_type == 2) {
		if (phy_c3.re > 127)
			phy_c15 = phy_c3.re - 256;
		if (phy_c3.im > 127)
			phy_c16 = phy_c3.im - 256;
	}
	wlc_lcnphy_set_cc(pi, cal_type, phy_c15, phy_c16);
	udelay(20);
	for (phy_c8 = 0; phy_c7 != 0 && phy_c8 < num_levels; phy_c8++) {
		phy_c23 = true;
		phy_c22 = false;
		switch (cal_type) {
		case 0:
			phy_c10 = 511;
			break;
		case 2:
			phy_c10 = 127;
			break;
		case 3:
			phy_c10 = 15;
			break;
		case 4:
			phy_c10 = 15;
			break;
		}

		phy_c9 = read_phy_reg(pi, 0x93d);
		phy_c9 = 2 * phy_c9;
		phy_c24 = false;
		phy_c5 = 7;
		phy_c25 = true;
		while (1) {
			write_radio_reg(pi, RADIO_2064_REG026,
					(phy_c5 & 0x7) | ((phy_c5 & 0x7) << 4));
			udelay(50);
			phy_c22 = false;
			ptr[130] = 0;
			wlc_lcnphy_samp_cap(pi, 1, phy_c9, &ptr[0], 2);
			if (ptr[130] == 1)
				phy_c22 = true;
			if (phy_c22)
				phy_c5 -= 1;
			if ((phy_c22 != phy_c24) && (!phy_c25))
				break;
			if (!phy_c22)
				phy_c5 += 1;
			if (phy_c5 <= 0 || phy_c5 >= 7)
				break;
			phy_c24 = phy_c22;
			phy_c25 = false;
		}

		if (phy_c5 < 0)
			phy_c5 = 0;
		else if (phy_c5 > 7)
			phy_c5 = 7;

		for (k = -phy_c7; k <= phy_c7; k += phy_c7) {
			for (l = -phy_c7; l <= phy_c7; l += phy_c7) {
				phy_c11 = phy_c15 + k;
				phy_c12 = phy_c16 + l;

				if (phy_c11 < -phy_c10)
					phy_c11 = -phy_c10;
				else if (phy_c11 > phy_c10)
					phy_c11 = phy_c10;
				if (phy_c12 < -phy_c10)
					phy_c12 = -phy_c10;
				else if (phy_c12 > phy_c10)
					phy_c12 = phy_c10;
				wlc_lcnphy_set_cc(pi, cal_type, phy_c11,
						  phy_c12);
				udelay(20);
				wlc_lcnphy_samp_cap(pi, 0, 0, ptr, 2);

				phy_c18 = 0;
				phy_c19 = 0;
				for (j = 0; j < 128; j++) {
					if (cal_type != 0)
						phy_c6 = j % phy_c4;
					else
						phy_c6 = (2 * j) % phy_c4;

					phy_c2.re = phy_c1[phy_c6].re;
					phy_c2.im = phy_c1[phy_c6].im;
					phy_c17 = ptr[j];
					phy_c18 = phy_c18 + phy_c17 * phy_c2.re;
					phy_c19 = phy_c19 + phy_c17 * phy_c2.im;
				}

				phy_c18 = phy_c18 >> 10;
				phy_c19 = phy_c19 >> 10;
				phy_c20 = ((phy_c18 * phy_c18) +
					   (phy_c19 * phy_c19));

				if (phy_c23 || phy_c20 < phy_c21) {
					phy_c21 = phy_c20;
					phy_c13 = phy_c11;
					phy_c14 = phy_c12;
				}
				phy_c23 = false;
			}
		}
		phy_c23 = true;
		phy_c15 = phy_c13;
		phy_c16 = phy_c14;
		phy_c7 = phy_c7 >> 1;
		wlc_lcnphy_set_cc(pi, cal_type, phy_c15, phy_c16);
		udelay(20);
	}
	goto cleanup;
cleanup:
	wlc_lcnphy_tx_iqlo_loopback_cleanup(pi, phy_c32);
	wlc_lcnphy_stop_tx_tone(pi);
	write_phy_reg(pi, 0x6da, phy_c26);
	write_phy_reg(pi, 0x6db, phy_c27);
	write_phy_reg(pi, 0x938, phy_c28);
	write_phy_reg(pi, 0x4d7, phy_c29);
	write_phy_reg(pi, 0x4d8, phy_c30);
	write_radio_reg(pi, RADIO_2064_REG026, phy_c31);

	kfree(phy_c32);
	kfree(ptr);
}