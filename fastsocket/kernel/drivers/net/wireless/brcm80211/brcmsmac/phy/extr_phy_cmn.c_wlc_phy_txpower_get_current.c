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
typedef  size_t uint ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct tx_power {int rf_cores; int flags; int* est_Pout; int* est_Pout_act; scalar_t__ est_Pout_cck; int /*<<< orphan*/ * tx_power_max_rate_ind; int /*<<< orphan*/ * tx_power_max; int /*<<< orphan*/ * target; scalar_t__* board_limit; int /*<<< orphan*/ * user_limit; } ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {scalar_t__ nphy_txpwrctrl; scalar_t__ radiopwr_override; int /*<<< orphan*/  tx_power_max_rate_ind; int /*<<< orphan*/  tx_power_max; TYPE_1__* sh; scalar_t__ hwpwrctrl; int /*<<< orphan*/ * tx_power_target; int /*<<< orphan*/ * tx_user_target; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {scalar_t__ up; int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 scalar_t__ PHY_TPC_HW_ON ; 
 scalar_t__ RADIOPWR_OVERRIDE_DEF ; 
 size_t TXP_LAST_OFDM ; 
 size_t TXP_LAST_OFDM_20_CDD ; 
 size_t TXP_NUM_RATES ; 
 int WL_TX_POWER_F_ENABLED ; 
 int WL_TX_POWER_F_HW ; 
 int WL_TX_POWER_F_MIMO ; 
 int WL_TX_POWER_F_SISO ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tssi (struct brcms_phy*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wlc_phy_tpc_isenabled_lcnphy (struct brcms_phy*) ; 
 int wlc_phy_txpower_est_power_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpower_sromlimit (struct brcms_phy_pub*,size_t,scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  wlc_phyreg_enter (struct brcms_phy_pub*) ; 
 int /*<<< orphan*/  wlc_phyreg_exit (struct brcms_phy_pub*) ; 

void
wlc_phy_txpower_get_current(struct brcms_phy_pub *ppi, struct tx_power *power,
			    uint channel)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	uint rate, num_rates;
	u8 min_pwr, max_pwr;

#if WL_TX_POWER_RATES != TXP_NUM_RATES
#error "struct tx_power out of sync with this fn"
#endif

	if (ISNPHY(pi)) {
		power->rf_cores = 2;
		power->flags |= (WL_TX_POWER_F_MIMO);
		if (pi->nphy_txpwrctrl == PHY_TPC_HW_ON)
			power->flags |=
				(WL_TX_POWER_F_ENABLED | WL_TX_POWER_F_HW);
	} else if (ISLCNPHY(pi)) {
		power->rf_cores = 1;
		power->flags |= (WL_TX_POWER_F_SISO);
		if (pi->radiopwr_override == RADIOPWR_OVERRIDE_DEF)
			power->flags |= WL_TX_POWER_F_ENABLED;
		if (pi->hwpwrctrl)
			power->flags |= WL_TX_POWER_F_HW;
	}

	num_rates = ((ISNPHY(pi)) ? (TXP_NUM_RATES) :
		     ((ISLCNPHY(pi)) ?
		      (TXP_LAST_OFDM_20_CDD + 1) : (TXP_LAST_OFDM + 1)));

	for (rate = 0; rate < num_rates; rate++) {
		power->user_limit[rate] = pi->tx_user_target[rate];
		wlc_phy_txpower_sromlimit(ppi, channel, &min_pwr, &max_pwr,
					  rate);
		power->board_limit[rate] = (u8) max_pwr;
		power->target[rate] = pi->tx_power_target[rate];
	}

	if (ISNPHY(pi)) {
		u32 est_pout;

		wlapi_suspend_mac_and_wait(pi->sh->physhim);
		wlc_phyreg_enter((struct brcms_phy_pub *) pi);
		est_pout = wlc_phy_txpower_est_power_nphy(pi);
		wlc_phyreg_exit((struct brcms_phy_pub *) pi);
		wlapi_enable_mac(pi->sh->physhim);

		power->est_Pout[0] = (est_pout >> 8) & 0xff;
		power->est_Pout[1] = est_pout & 0xff;

		power->est_Pout_act[0] = est_pout >> 24;
		power->est_Pout_act[1] = (est_pout >> 16) & 0xff;

		if (power->est_Pout[0] == 0x80)
			power->est_Pout[0] = 0;
		if (power->est_Pout[1] == 0x80)
			power->est_Pout[1] = 0;

		if (power->est_Pout_act[0] == 0x80)
			power->est_Pout_act[0] = 0;
		if (power->est_Pout_act[1] == 0x80)
			power->est_Pout_act[1] = 0;

		power->est_Pout_cck = 0;

		power->tx_power_max[0] = pi->tx_power_max;
		power->tx_power_max[1] = pi->tx_power_max;

		power->tx_power_max_rate_ind[0] = pi->tx_power_max_rate_ind;
		power->tx_power_max_rate_ind[1] = pi->tx_power_max_rate_ind;
	} else if (pi->hwpwrctrl && pi->sh->up) {

		wlc_phyreg_enter(ppi);
		if (ISLCNPHY(pi)) {

			power->tx_power_max[0] = pi->tx_power_max;
			power->tx_power_max[1] = pi->tx_power_max;

			power->tx_power_max_rate_ind[0] =
				pi->tx_power_max_rate_ind;
			power->tx_power_max_rate_ind[1] =
				pi->tx_power_max_rate_ind;

			if (wlc_phy_tpc_isenabled_lcnphy(pi))
				power->flags |=
					(WL_TX_POWER_F_HW |
					 WL_TX_POWER_F_ENABLED);
			else
				power->flags &=
					~(WL_TX_POWER_F_HW |
					  WL_TX_POWER_F_ENABLED);

			wlc_lcnphy_get_tssi(pi, (s8 *) &power->est_Pout[0],
					    (s8 *) &power->est_Pout_cck);
		}
		wlc_phyreg_exit(ppi);
	}
}