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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy_lcnphy {int /*<<< orphan*/  lcnphy_current_index; } ;
struct TYPE_4__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {int phy_forcecal; TYPE_1__* sh; int /*<<< orphan*/  phy_lastcal; int /*<<< orphan*/  d11core; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_3__ {int /*<<< orphan*/  physhim; int /*<<< orphan*/  now; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_EN_MAC ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_deaf_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_txpwrtbl_iqlo_cal (struct brcms_phy*) ; 

__attribute__((used)) static void wlc_lcnphy_glacial_timer_based_cal(struct brcms_phy *pi)
{
	bool suspend;
	s8 index;
	u16 SAVE_pwrctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;
	suspend = (0 == (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	if (!suspend)
		wlapi_suspend_mac_and_wait(pi->sh->physhim);
	wlc_lcnphy_deaf_mode(pi, true);
	pi->phy_lastcal = pi->sh->now;
	pi->phy_forcecal = false;
	index = pi_lcn->lcnphy_current_index;

	wlc_lcnphy_txpwrtbl_iqlo_cal(pi);

	wlc_lcnphy_set_tx_pwr_by_index(pi, index);
	wlc_lcnphy_set_tx_pwr_ctrl(pi, SAVE_pwrctrl);
	wlc_lcnphy_deaf_mode(pi, false);
	if (!suspend)
		wlapi_enable_mac(pi->sh->physhim);

}