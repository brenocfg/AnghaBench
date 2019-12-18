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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  radio_chanspec; } ;
struct TYPE_4__ {int ptcentreTs20; int ptcentreFactor; } ;
struct TYPE_3__ {int boardflags; } ;

/* Variables and functions */
 int BFL_FEM ; 
 int CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 TYPE_2__* lcnphy_sfo_cfg ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_lcnphy_load_tx_iir_filter (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_radio_2064_channel_tune_4313 (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_chanspec_tweaks (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_toggle_afe_pwdn (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_radio_set (struct brcms_phy_pub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_phy_chanspec_set_lcnphy(struct brcms_phy *pi, u16 chanspec)
{
	u8 channel = CHSPEC_CHANNEL(chanspec);

	wlc_phy_chanspec_radio_set((struct brcms_phy_pub *)pi, chanspec);

	wlc_lcnphy_set_chanspec_tweaks(pi, pi->radio_chanspec);

	or_phy_reg(pi, 0x44a, 0x44);
	write_phy_reg(pi, 0x44a, 0x80);

	wlc_lcnphy_radio_2064_channel_tune_4313(pi, channel);
	udelay(1000);

	wlc_lcnphy_toggle_afe_pwdn(pi);

	write_phy_reg(pi, 0x657, lcnphy_sfo_cfg[channel - 1].ptcentreTs20);
	write_phy_reg(pi, 0x658, lcnphy_sfo_cfg[channel - 1].ptcentreFactor);

	if (CHSPEC_CHANNEL(pi->radio_chanspec) == 14) {
		mod_phy_reg(pi, 0x448, (0x3 << 8), (2) << 8);

		wlc_lcnphy_load_tx_iir_filter(pi, false, 3);
	} else {
		mod_phy_reg(pi, 0x448, (0x3 << 8), (1) << 8);

		wlc_lcnphy_load_tx_iir_filter(pi, false, 2);
	}

	if (pi->sh->boardflags & BFL_FEM)
		wlc_lcnphy_load_tx_iir_filter(pi, true, 0);
	else
		wlc_lcnphy_load_tx_iir_filter(pi, true, 3);

	mod_phy_reg(pi, 0x4eb, (0x7 << 3), (1) << 3);
}