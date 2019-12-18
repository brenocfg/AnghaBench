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
typedef  int u8 ;
typedef  int u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;
typedef  scalar_t__ s32 ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;

/* Variables and functions */
 int /*<<< orphan*/  B2055_C1_PD_RSSIMISC ; 
 int /*<<< orphan*/  B2055_C1_PD_RXTX ; 
 int /*<<< orphan*/  B2055_C1_SP_RSSI ; 
 int /*<<< orphan*/  B2055_C2_PD_RSSIMISC ; 
 int /*<<< orphan*/  B2055_C2_PD_RXTX ; 
 int /*<<< orphan*/  B2055_C2_SP_RSSI ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_INTC2 ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int N_RAIL_I ; 
 int N_RAIL_Q ; 
 int N_RSSI_NB ; 
 int N_RSSI_W1 ; 
 int N_RSSI_W2 ; 
 int abs (scalar_t__) ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int b43_nphy_classifier (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_nphy_poll_rssi (struct b43_wldev*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  b43_nphy_read_clip_detection (struct b43_wldev*,int*) ; 
 int /*<<< orphan*/  b43_nphy_reset_cca (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_rssi_select (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_nphy_scale_offset_rssi (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  b43_nphy_set_rssi_2055_vcm (struct b43_wldev*,int,int*) ; 
 int /*<<< orphan*/  b43_nphy_write_clip_detection (struct b43_wldev*,int*) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void b43_nphy_rev2_rssi_cal(struct b43_wldev *dev, enum n_rssi_type type)
{
	int i, j, vcm;
	u8 state[4];
	u8 code, val;
	u16 class, override;
	u8 regs_save_radio[2];
	u16 regs_save_phy[2];

	s32 offset[4];
	u8 core;
	u8 rail;

	u16 clip_state[2];
	u16 clip_off[2] = { 0xFFFF, 0xFFFF };
	s32 results_min[4] = { };
	u8 vcm_final[4] = { };
	s32 results[4][4] = { };
	s32 miniq[4][2] = { };

	if (type == N_RSSI_NB) {
		code = 0;
		val = 6;
	} else if (type == N_RSSI_W1 || type == N_RSSI_W2) {
		code = 25;
		val = 4;
	} else {
		B43_WARN_ON(1);
		return;
	}

	class = b43_nphy_classifier(dev, 0, 0);
	b43_nphy_classifier(dev, 7, 4);
	b43_nphy_read_clip_detection(dev, clip_state);
	b43_nphy_write_clip_detection(dev, clip_off);

	if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ)
		override = 0x140;
	else
		override = 0x110;

	regs_save_phy[0] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC1);
	regs_save_radio[0] = b43_radio_read(dev, B2055_C1_PD_RXTX);
	b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, override);
	b43_radio_write(dev, B2055_C1_PD_RXTX, val);

	regs_save_phy[1] = b43_phy_read(dev, B43_NPHY_RFCTL_INTC2);
	regs_save_radio[1] = b43_radio_read(dev, B2055_C2_PD_RXTX);
	b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, override);
	b43_radio_write(dev, B2055_C2_PD_RXTX, val);

	state[0] = b43_radio_read(dev, B2055_C1_PD_RSSIMISC) & 0x07;
	state[1] = b43_radio_read(dev, B2055_C2_PD_RSSIMISC) & 0x07;
	b43_radio_mask(dev, B2055_C1_PD_RSSIMISC, 0xF8);
	b43_radio_mask(dev, B2055_C2_PD_RSSIMISC, 0xF8);
	state[2] = b43_radio_read(dev, B2055_C1_SP_RSSI) & 0x07;
	state[3] = b43_radio_read(dev, B2055_C2_SP_RSSI) & 0x07;

	b43_nphy_rssi_select(dev, 5, type);
	b43_nphy_scale_offset_rssi(dev, 0, 0, 5, N_RAIL_I, type);
	b43_nphy_scale_offset_rssi(dev, 0, 0, 5, N_RAIL_Q, type);

	for (vcm = 0; vcm < 4; vcm++) {
		u8 tmp[4];
		for (j = 0; j < 4; j++)
			tmp[j] = vcm;
		if (type != N_RSSI_W2)
			b43_nphy_set_rssi_2055_vcm(dev, type, tmp);
		b43_nphy_poll_rssi(dev, type, results[vcm], 8);
		if (type == N_RSSI_W1 || type == N_RSSI_W2)
			for (j = 0; j < 2; j++)
				miniq[vcm][j] = min(results[vcm][2 * j],
						    results[vcm][2 * j + 1]);
	}

	for (i = 0; i < 4; i++) {
		s32 mind = 0x100000;
		u8 minvcm = 0;
		s32 minpoll = 249;
		s32 currd;
		for (vcm = 0; vcm < 4; vcm++) {
			if (type == N_RSSI_NB)
				currd = abs(results[vcm][i] - code * 8);
			else
				currd = abs(miniq[vcm][i / 2] - code * 8);

			if (currd < mind) {
				mind = currd;
				minvcm = vcm;
			}

			if (results[vcm][i] < minpoll)
				minpoll = results[vcm][i];
		}
		results_min[i] = minpoll;
		vcm_final[i] = minvcm;
	}

	if (type != N_RSSI_W2)
		b43_nphy_set_rssi_2055_vcm(dev, type, vcm_final);

	for (i = 0; i < 4; i++) {
		offset[i] = (code * 8) - results[vcm_final[i]][i];

		if (offset[i] < 0)
			offset[i] = -((abs(offset[i]) + 4) / 8);
		else
			offset[i] = (offset[i] + 4) / 8;

		if (results_min[i] == 248)
			offset[i] = code - 32;

		core = (i / 2) ? 2 : 1;
		rail = (i % 2) ? N_RAIL_Q : N_RAIL_I;

		b43_nphy_scale_offset_rssi(dev, 0, offset[i], core, rail,
						type);
	}

	b43_radio_maskset(dev, B2055_C1_PD_RSSIMISC, 0xF8, state[0]);
	b43_radio_maskset(dev, B2055_C2_PD_RSSIMISC, 0xF8, state[1]);

	switch (state[2]) {
	case 1:
		b43_nphy_rssi_select(dev, 1, N_RSSI_NB);
		break;
	case 4:
		b43_nphy_rssi_select(dev, 1, N_RSSI_W1);
		break;
	case 2:
		b43_nphy_rssi_select(dev, 1, N_RSSI_W2);
		break;
	default:
		b43_nphy_rssi_select(dev, 1, N_RSSI_W2);
		break;
	}

	switch (state[3]) {
	case 1:
		b43_nphy_rssi_select(dev, 2, N_RSSI_NB);
		break;
	case 4:
		b43_nphy_rssi_select(dev, 2, N_RSSI_W1);
		break;
	default:
		b43_nphy_rssi_select(dev, 2, N_RSSI_W2);
		break;
	}

	b43_nphy_rssi_select(dev, 0, type);

	b43_phy_write(dev, B43_NPHY_RFCTL_INTC1, regs_save_phy[0]);
	b43_radio_write(dev, B2055_C1_PD_RXTX, regs_save_radio[0]);
	b43_phy_write(dev, B43_NPHY_RFCTL_INTC2, regs_save_phy[1]);
	b43_radio_write(dev, B2055_C2_PD_RXTX, regs_save_radio[1]);

	b43_nphy_classifier(dev, 7, class);
	b43_nphy_write_clip_detection(dev, clip_state);
	/* Specs don't say about reset here, but it makes wl and b43 dumps
	   identical, it really seems wl performs this */
	b43_nphy_reset_cca(dev);
}