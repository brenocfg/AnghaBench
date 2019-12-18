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
typedef  int u16 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy_lcnphy {int lcnphy_current_index; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_1__ u; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int wlc_lcnphy_tempcompensated_txpwrctrl (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 

void wlc_lcnphy_tx_power_adjustment(struct brcms_phy_pub *ppi)
{
	s8 index;
	u16 index2;
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;
	u16 SAVE_txpwrctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
	if (wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi) &&
	    SAVE_txpwrctrl) {
		index = wlc_lcnphy_tempcompensated_txpwrctrl(pi);
		index2 = (u16) (index * 2);
		mod_phy_reg(pi, 0x4a9, (0x1ff << 0), (index2) << 0);

		pi_lcn->lcnphy_current_index =
			(s8)((read_phy_reg(pi, 0x4a9) & 0xFF) / 2);
	}
}