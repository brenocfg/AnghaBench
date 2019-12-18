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
typedef  int u32 ;
typedef  int u16 ;
struct link_vars {int dummy; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_ADV1 ; 
 int MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_LP_ADV1 ; 
 int MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV ; 
 int MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1 ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_IEEEB1 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_pause_resolve (struct link_vars*,int) ; 

__attribute__((used)) static void bnx2x_update_adv_fc(struct bnx2x_phy *phy,
				struct link_params *params,
				struct link_vars *vars,
				u32 gp_status)
{
	u16 ld_pause;   /* local driver */
	u16 lp_pause;   /* link partner */
	u16 pause_result;
	struct bnx2x *bp = params->bp;
	if ((gp_status &
	     (MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE |
	      MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE)) ==
	    (MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE |
	     MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE)) {

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV1,
				  &ld_pause);
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_LP_ADV1,
				  &lp_pause);
		pause_result = (ld_pause &
				MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK) >> 8;
		pause_result |= (lp_pause &
				 MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_MASK) >> 10;
		DP(NETIF_MSG_LINK, "pause_result CL73 0x%x\n", pause_result);
	} else {
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_AUTO_NEG_ADV,
				  &ld_pause);
		CL22_RD_OVER_CL45(bp, phy,
			MDIO_REG_BANK_COMBO_IEEE0,
			MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1,
			&lp_pause);
		pause_result = (ld_pause &
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK)>>5;
		pause_result |= (lp_pause &
				 MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK)>>7;
		DP(NETIF_MSG_LINK, "pause_result CL37 0x%x\n", pause_result);
	}
	bnx2x_pause_resolve(vars, pause_result);

}