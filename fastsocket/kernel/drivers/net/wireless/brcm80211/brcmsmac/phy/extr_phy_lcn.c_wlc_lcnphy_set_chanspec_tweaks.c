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
struct brcms_phy_lcnphy {int lcnphy_bandedge_corr; int lcnphy_spurmod; } ;
struct TYPE_3__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_2__* sh; TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  sih; } ;

/* Variables and functions */
 int CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  si_pmu_pllcontrol (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  si_pmu_pllupd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_txrx_spur_avoidance_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_lcnphy_set_chanspec_tweaks(struct brcms_phy *pi, u16 chanspec)
{
	u8 channel = CHSPEC_CHANNEL(chanspec);
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	if (channel == 14)
		mod_phy_reg(pi, 0x448, (0x3 << 8), (2) << 8);
	else
		mod_phy_reg(pi, 0x448, (0x3 << 8), (1) << 8);

	pi_lcn->lcnphy_bandedge_corr = 2;
	if (channel == 1)
		pi_lcn->lcnphy_bandedge_corr = 4;

	if (channel == 1 || channel == 2 || channel == 3 ||
	    channel == 4 || channel == 9 ||
	    channel == 10 || channel == 11 || channel == 12) {
		si_pmu_pllcontrol(pi->sh->sih, 0x2, 0xffffffff, 0x03000c04);
		si_pmu_pllcontrol(pi->sh->sih, 0x3, 0xffffff, 0x0);
		si_pmu_pllcontrol(pi->sh->sih, 0x4, 0xffffffff, 0x200005c0);

		si_pmu_pllupd(pi->sh->sih);
		write_phy_reg(pi, 0x942, 0);
		wlc_lcnphy_txrx_spur_avoidance_mode(pi, false);
		pi_lcn->lcnphy_spurmod = false;
		mod_phy_reg(pi, 0x424, (0xff << 8), (0x1b) << 8);

		write_phy_reg(pi, 0x425, 0x5907);
	} else {
		si_pmu_pllcontrol(pi->sh->sih, 0x2, 0xffffffff, 0x03140c04);
		si_pmu_pllcontrol(pi->sh->sih, 0x3, 0xffffff, 0x333333);
		si_pmu_pllcontrol(pi->sh->sih, 0x4, 0xffffffff, 0x202c2820);

		si_pmu_pllupd(pi->sh->sih);
		write_phy_reg(pi, 0x942, 0);
		wlc_lcnphy_txrx_spur_avoidance_mode(pi, true);

		pi_lcn->lcnphy_spurmod = false;
		mod_phy_reg(pi, 0x424, (0xff << 8), (0x1f) << 8);

		write_phy_reg(pi, 0x425, 0x590a);
	}

	or_phy_reg(pi, 0x44a, 0x44);
	write_phy_reg(pi, 0x44a, 0x80);
}