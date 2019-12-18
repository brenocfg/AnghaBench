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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_PERICAL_TEMPBASED_TXPWRCTRL ; 
 int /*<<< orphan*/  LCNPHY_TX_PWR_CTRL_OFF ; 
 int /*<<< orphan*/  wlc_lcnphy_calib_modes (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 scalar_t__ wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_tssi_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_txpower_recalc_target (struct brcms_phy*) ; 

void wlc_phy_txpower_recalc_target_lcnphy(struct brcms_phy *pi)
{
	u16 pwr_ctrl;
	if (wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi)) {
		wlc_lcnphy_calib_modes(pi, LCNPHY_PERICAL_TEMPBASED_TXPWRCTRL);
	} else if (wlc_lcnphy_tssi_based_pwr_ctrl_enabled(pi)) {
		pwr_ctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
		wlc_lcnphy_set_tx_pwr_ctrl(pi, LCNPHY_TX_PWR_CTRL_OFF);
		wlc_lcnphy_txpower_recalc_target(pi);
		wlc_lcnphy_set_tx_pwr_ctrl(pi, pwr_ctrl);
	}
}