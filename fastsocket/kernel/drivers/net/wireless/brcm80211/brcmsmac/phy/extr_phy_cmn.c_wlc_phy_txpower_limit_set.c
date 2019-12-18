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
typedef  int /*<<< orphan*/  u16 ;
struct txpwr_limits {scalar_t__* ofdm; scalar_t__* mcs_20_siso; } ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {TYPE_1__* sh; scalar_t__* txpwr_limit; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int BRCMS_NUM_RATES_MCS_1_STREAM ; 
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 int TXP_FIRST_OFDM_20_CDD ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_cal_txpower_recalc_sw (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpower_recalc_target (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpower_reg_limit_calc (struct brcms_phy*,struct txpwr_limits*,int /*<<< orphan*/ ) ; 

void
wlc_phy_txpower_limit_set(struct brcms_phy_pub *ppi, struct txpwr_limits *txpwr,
			  u16 chanspec)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;

	wlc_phy_txpower_reg_limit_calc(pi, txpwr, chanspec);

	if (ISLCNPHY(pi)) {
		int i, j;
		for (i = TXP_FIRST_OFDM_20_CDD, j = 0;
		     j < BRCMS_NUM_RATES_MCS_1_STREAM; i++, j++) {
			if (txpwr->mcs_20_siso[j])
				pi->txpwr_limit[i] = txpwr->mcs_20_siso[j];
			else
				pi->txpwr_limit[i] = txpwr->ofdm[j];
		}
	}

	wlapi_suspend_mac_and_wait(pi->sh->physhim);

	wlc_phy_txpower_recalc_target(pi);
	wlc_phy_cal_txpower_recalc_sw(pi);
	wlapi_enable_mac(pi->sh->physhim);
}