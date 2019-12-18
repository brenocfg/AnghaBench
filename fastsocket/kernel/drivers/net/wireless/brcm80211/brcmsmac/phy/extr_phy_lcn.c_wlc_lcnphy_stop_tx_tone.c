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
struct brcms_phy_lcnphy {scalar_t__ lcnphy_spurmod; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {scalar_t__ phy_tx_tone_freq; TYPE_1__ u; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_2064_REG112 ; 
 int /*<<< orphan*/  and_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_deaf_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_pu (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_txrx_spur_avoidance_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_lcnphy_stop_tx_tone(struct brcms_phy *pi)
{
	s16 playback_status;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	pi->phy_tx_tone_freq = 0;
	if (pi_lcn->lcnphy_spurmod) {
		write_phy_reg(pi, 0x942, 0x7);
		write_phy_reg(pi, 0x93b, 0x2017);
		write_phy_reg(pi, 0x93c, 0x27c5);
		wlc_lcnphy_txrx_spur_avoidance_mode(pi, true);
	}

	playback_status = read_phy_reg(pi, 0x644);
	if (playback_status & (0x1 << 0)) {
		wlc_lcnphy_tx_pu(pi, 0);
		mod_phy_reg(pi, 0x63f, (0x1 << 1), 1 << 1);
	} else if (playback_status & (0x1 << 1))
		mod_phy_reg(pi, 0x453, (0x1 << 15), 0 << 15);

	mod_phy_reg(pi, 0x6d6, (0x3 << 0), 1 << 0);

	mod_phy_reg(pi, 0x6da, (0x1 << 3), 0 << 3);

	mod_phy_reg(pi, 0x6da, (0x1 << 7), 0 << 7);

	and_radio_reg(pi, RADIO_2064_REG112, 0xFFF9);

	wlc_lcnphy_deaf_mode(pi, false);
}