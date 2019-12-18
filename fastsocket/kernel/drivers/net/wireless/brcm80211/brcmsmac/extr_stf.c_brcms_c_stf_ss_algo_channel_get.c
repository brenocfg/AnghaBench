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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct tx_power {scalar_t__* target; } ;
struct brcms_c_info {TYPE_2__* band; TYPE_1__* pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  pi; } ;
struct TYPE_3__ {int /*<<< orphan*/  up; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSPEC_CHANNEL (scalar_t__) ; 
 scalar_t__ CHSPEC_IS40 (scalar_t__) ; 
 int /*<<< orphan*/  PHY_TXC1_MODE_CDD ; 
 int /*<<< orphan*/  PHY_TXC1_MODE_SISO ; 
 int /*<<< orphan*/  PHY_TXC1_MODE_STBC ; 
 size_t WL_TX_POWER_MCS20_CDD_FIRST ; 
 size_t WL_TX_POWER_MCS20_SISO_FIRST ; 
 size_t WL_TX_POWER_MCS20_STBC_FIRST ; 
 size_t WL_TX_POWER_MCS40_CDD_FIRST ; 
 size_t WL_TX_POWER_MCS40_SISO_FIRST ; 
 size_t WL_TX_POWER_MCS40_STBC_FIRST ; 
 int /*<<< orphan*/  setbit (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_txpower_get_current (int /*<<< orphan*/ ,struct tx_power*,int /*<<< orphan*/ ) ; 

void
brcms_c_stf_ss_algo_channel_get(struct brcms_c_info *wlc, u16 *ss_algo_channel,
			    u16 chanspec)
{
	struct tx_power power;
	u8 siso_mcs_id, cdd_mcs_id, stbc_mcs_id;

	/* Clear previous settings */
	*ss_algo_channel = 0;

	if (!wlc->pub->up) {
		*ss_algo_channel = (u16) -1;
		return;
	}

	wlc_phy_txpower_get_current(wlc->band->pi, &power,
				    CHSPEC_CHANNEL(chanspec));

	siso_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WL_TX_POWER_MCS40_SISO_FIRST : WL_TX_POWER_MCS20_SISO_FIRST;
	cdd_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WL_TX_POWER_MCS40_CDD_FIRST : WL_TX_POWER_MCS20_CDD_FIRST;
	stbc_mcs_id = (CHSPEC_IS40(chanspec)) ?
	    WL_TX_POWER_MCS40_STBC_FIRST : WL_TX_POWER_MCS20_STBC_FIRST;

	/* criteria to choose stf mode */

	/*
	 * the "+3dbm (12 0.25db units)" is to account for the fact that with
	 * CDD, tx occurs on both chains
	 */
	if (power.target[siso_mcs_id] > (power.target[cdd_mcs_id] + 12))
		setbit(ss_algo_channel, PHY_TXC1_MODE_SISO);
	else
		setbit(ss_algo_channel, PHY_TXC1_MODE_CDD);

	/*
	 * STBC is ORed into to algo channel as STBC requires per-packet SCB
	 * capability check so cannot be default mode of operation. One of
	 * SISO, CDD have to be set
	 */
	if (power.target[siso_mcs_id] <= (power.target[stbc_mcs_id] + 12))
		setbit(ss_algo_channel, PHY_TXC1_MODE_STBC);
}