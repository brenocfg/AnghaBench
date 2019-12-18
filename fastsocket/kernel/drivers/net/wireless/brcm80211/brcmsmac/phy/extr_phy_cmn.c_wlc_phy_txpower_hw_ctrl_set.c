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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int hwpwrctrl; int nphy_txpwrctrl; int txpwrctrl; TYPE_1__* sh; int /*<<< orphan*/  saved_txpwr_idx; int /*<<< orphan*/  d11core; int /*<<< orphan*/  hwpwrctrl_capable; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int MCTL_EN_MAC ; 
 scalar_t__ PHY_TPC_HW_OFF ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_fixpower_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_enable_nphy (struct brcms_phy*,int) ; 

void wlc_phy_txpower_hw_ctrl_set(struct brcms_phy_pub *ppi, bool hwpwrctrl)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	bool suspend;

	if (!pi->hwpwrctrl_capable)
		return;

	pi->hwpwrctrl = hwpwrctrl;
	pi->nphy_txpwrctrl = hwpwrctrl;
	pi->txpwrctrl = hwpwrctrl;

	if (ISNPHY(pi)) {
		suspend = (0 == (bcma_read32(pi->d11core,
					     D11REGOFFS(maccontrol)) &
				 MCTL_EN_MAC));
		if (!suspend)
			wlapi_suspend_mac_and_wait(pi->sh->physhim);

		wlc_phy_txpwrctrl_enable_nphy(pi, pi->nphy_txpwrctrl);
		if (pi->nphy_txpwrctrl == PHY_TPC_HW_OFF)
			wlc_phy_txpwr_fixpower_nphy(pi);
		else
			mod_phy_reg(pi, 0x1e7, (0x7f << 0),
				    pi->saved_txpwr_idx);

		if (!suspend)
			wlapi_enable_mac(pi->sh->physhim);
	}
}