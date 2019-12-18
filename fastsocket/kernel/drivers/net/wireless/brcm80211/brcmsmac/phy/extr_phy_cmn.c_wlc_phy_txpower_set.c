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
typedef  int uint ;
typedef  scalar_t__ u8 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int txpwroverride; TYPE_1__* sh; int /*<<< orphan*/  d11core; scalar_t__* tx_user_target; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; scalar_t__ up; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  SCAN_INPROG_PHY (struct brcms_phy*) ; 
 int TXP_NUM_RATES ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_cal_txpower_recalc_sw (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpower_recalc_target (struct brcms_phy*) ; 

int wlc_phy_txpower_set(struct brcms_phy_pub *ppi, uint qdbm, bool override)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	int i;

	if (qdbm > 127)
		return -EINVAL;

	for (i = 0; i < TXP_NUM_RATES; i++)
		pi->tx_user_target[i] = (u8) qdbm;

	pi->txpwroverride = false;

	if (pi->sh->up) {
		if (!SCAN_INPROG_PHY(pi)) {
			bool suspend;

			suspend = (0 == (bcma_read32(pi->d11core,
						     D11REGOFFS(maccontrol)) &
					 MCTL_EN_MAC));

			if (!suspend)
				wlapi_suspend_mac_and_wait(pi->sh->physhim);

			wlc_phy_txpower_recalc_target(pi);
			wlc_phy_cal_txpower_recalc_sw(pi);

			if (!suspend)
				wlapi_enable_mac(pi->sh->physhim);
		}
	}
	return 0;
}