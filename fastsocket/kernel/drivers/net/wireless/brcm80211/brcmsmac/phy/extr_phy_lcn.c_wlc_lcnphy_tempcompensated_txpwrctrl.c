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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct brcms_phy_lcnphy {int lcnphy_current_index; int lcnphy_tempsense_slope; int lcnphy_measPower; int lcnphy_tempsense_option; int lcnphy_tempcorrx; int lcnphy_bandedge_corr; scalar_t__ lcnphy_rawtempsense; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_rev; } ;
struct TYPE_3__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {scalar_t__ tx_power_min; TYPE_2__ pubpi; TYPE_1__ u; } ;
typedef  int s8 ;
typedef  int s16 ;

/* Variables and functions */
 int FIXED_TXPWR ; 
 int LCNPHY_TEMPSENSE (scalar_t__) ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlc_lcnphy_qdiv_roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wlc_lcnphy_tempsense (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 scalar_t__ wlc_lcnphy_tssi_based_pwr_ctrl_enabled (struct brcms_phy*) ; 

__attribute__((used)) static s8 wlc_lcnphy_tempcompensated_txpwrctrl(struct brcms_phy *pi)
{
	s8 index, delta_brd, delta_temp, new_index, tempcorrx;
	s16 manp, meas_temp, temp_diff;
	bool neg = false;
	u16 temp;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	if (wlc_lcnphy_tssi_based_pwr_ctrl_enabled(pi))
		return pi_lcn->lcnphy_current_index;

	index = FIXED_TXPWR;

	if (pi_lcn->lcnphy_tempsense_slope == 0)
		return index;

	temp = (u16) wlc_lcnphy_tempsense(pi, 0);
	meas_temp = LCNPHY_TEMPSENSE(temp);

	if (pi->tx_power_min != 0)
		delta_brd = (pi_lcn->lcnphy_measPower - pi->tx_power_min);
	else
		delta_brd = 0;

	manp = LCNPHY_TEMPSENSE(pi_lcn->lcnphy_rawtempsense);
	temp_diff = manp - meas_temp;
	if (temp_diff < 0) {
		neg = true;
		temp_diff = -temp_diff;
	}

	delta_temp = (s8) wlc_lcnphy_qdiv_roundup((u32) (temp_diff * 192),
						  (u32) (pi_lcn->
							 lcnphy_tempsense_slope
							 * 10), 0);
	if (neg)
		delta_temp = -delta_temp;

	if (pi_lcn->lcnphy_tempsense_option == 3
	    && LCNREV_IS(pi->pubpi.phy_rev, 0))
		delta_temp = 0;
	if (pi_lcn->lcnphy_tempcorrx > 31)
		tempcorrx = (s8) (pi_lcn->lcnphy_tempcorrx - 64);
	else
		tempcorrx = (s8) pi_lcn->lcnphy_tempcorrx;
	if (LCNREV_IS(pi->pubpi.phy_rev, 1))
		tempcorrx = 4;
	new_index =
		index + delta_brd + delta_temp - pi_lcn->lcnphy_bandedge_corr;
	new_index += tempcorrx;

	if (LCNREV_IS(pi->pubpi.phy_rev, 1))
		index = 127;

	if (new_index < 0 || new_index > 126)
		return index;

	return new_index;
}