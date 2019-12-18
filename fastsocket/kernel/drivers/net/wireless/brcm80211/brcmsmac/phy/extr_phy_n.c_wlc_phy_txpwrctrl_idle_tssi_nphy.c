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
typedef  void* u8 ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_2__* nphy_pwrctrl_info; TYPE_1__ pubpi; } ;
typedef  int s32 ;
typedef  scalar_t__ int_val ;
struct TYPE_4__ {void* idle_tssi_5g; void* idle_tssi_2g; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 scalar_t__ NPHY_RSSI_SEL_TSSI_2G ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 size_t PHY_CORE_0 ; 
 size_t PHY_CORE_1 ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 scalar_t__ PHY_MUTED (struct brcms_phy*) ; 
 scalar_t__ PLT_INPROG_PHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  RADIO_MIMO_CORESEL_OFF ; 
 scalar_t__ SCAN_RM_IN_PROGRESS (struct brcms_phy*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_phy_ipa_internal_tssi_setup_nphy (struct brcms_phy*) ; 
 int wlc_phy_poll_rssi_nphy (struct brcms_phy*,void*,int*,int) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy (struct brcms_phy*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rssisel_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stopplayback_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_tx_tone_nphy (struct brcms_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wlc_phy_txpwrctrl_idle_tssi_nphy(struct brcms_phy *pi)
{
	s32 rssi_buf[4];
	s32 int_val;

	if (SCAN_RM_IN_PROGRESS(pi) || PLT_INPROG_PHY(pi) || PHY_MUTED(pi))

		return;

	if (PHY_IPA(pi))
		wlc_phy_ipa_internal_tssi_setup_nphy(pi);

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 12),
						  0, 0x3, 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);
	else if (NREV_GE(pi->pubpi.phy_rev, 3))
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 13), 0, 3, 0);

	wlc_phy_stopplayback_nphy(pi);

	wlc_phy_tx_tone_nphy(pi, 4000, 0, 0, 0, false);

	udelay(20);
	int_val =
		wlc_phy_poll_rssi_nphy(pi, (u8) NPHY_RSSI_SEL_TSSI_2G, rssi_buf,
				       1);
	wlc_phy_stopplayback_nphy(pi);
	wlc_phy_rssisel_nphy(pi, RADIO_MIMO_CORESEL_OFF, 0);

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 12),
						  0, 0x3, 1,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);
	else if (NREV_GE(pi->pubpi.phy_rev, 3))
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 13), 0, 3, 1);

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {

		pi->nphy_pwrctrl_info[PHY_CORE_0].idle_tssi_2g =
			(u8) ((int_val >> 24) & 0xff);
		pi->nphy_pwrctrl_info[PHY_CORE_0].idle_tssi_5g =
			(u8) ((int_val >> 24) & 0xff);

		pi->nphy_pwrctrl_info[PHY_CORE_1].idle_tssi_2g =
			(u8) ((int_val >> 8) & 0xff);
		pi->nphy_pwrctrl_info[PHY_CORE_1].idle_tssi_5g =
			(u8) ((int_val >> 8) & 0xff);
	} else {
		pi->nphy_pwrctrl_info[PHY_CORE_0].idle_tssi_2g =
			(u8) ((int_val >> 24) & 0xff);

		pi->nphy_pwrctrl_info[PHY_CORE_1].idle_tssi_2g =
			(u8) ((int_val >> 8) & 0xff);

		pi->nphy_pwrctrl_info[PHY_CORE_0].idle_tssi_5g =
			(u8) ((int_val >> 16) & 0xff);
		pi->nphy_pwrctrl_info[PHY_CORE_1].idle_tssi_5g =
			(u8) ((int_val) & 0xff);
	}

}