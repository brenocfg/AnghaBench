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
typedef  int u8 ;
typedef  int u16 ;
struct link_vars {int dummy; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_ADV_PAUSE ; 
 int MDIO_AN_REG_ADV_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LP ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG ; 
 int MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH ; 
 int /*<<< orphan*/  MDIO_WC_REG_GP2_STATUS_GP_2_4 ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_LP_AN_CAP ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_4_CL73_AN_CMPL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE ; 
 scalar_t__ SINGLE_MEDIA_DIRECT (struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_cl22_read (struct bnx2x*,struct bnx2x_phy*,int,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int bnx2x_get_warpcore_lane (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_pause_resolve (struct link_vars*,int) ; 

__attribute__((used)) static void bnx2x_ext_phy_update_adv_fc(struct bnx2x_phy *phy,
					struct link_params *params,
					struct link_vars *vars)
{
	u16 ld_pause;		/* local */
	u16 lp_pause;		/* link partner */
	u16 pause_result;
	struct bnx2x *bp = params->bp;
	if (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE) {
		bnx2x_cl22_read(bp, phy, 0x4, &ld_pause);
		bnx2x_cl22_read(bp, phy, 0x5, &lp_pause);
	} else if (CHIP_IS_E3(bp) &&
		SINGLE_MEDIA_DIRECT(params)) {
		u8 lane = bnx2x_get_warpcore_lane(phy, params);
		u16 gp_status, gp_mask;
		bnx2x_cl45_read(bp, phy,
				MDIO_AN_DEVAD, MDIO_WC_REG_GP2_STATUS_GP_2_4,
				&gp_status);
		gp_mask = (MDIO_WC_REG_GP2_STATUS_GP_2_4_CL73_AN_CMPL |
			   MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_LP_AN_CAP) <<
			lane;
		if ((gp_status & gp_mask) == gp_mask) {
			bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_ADV_PAUSE, &ld_pause);
			bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_LP_AUTO_NEG, &lp_pause);
		} else {
			bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_CL37_FC_LD, &ld_pause);
			bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_CL37_FC_LP, &lp_pause);
			ld_pause = ((ld_pause &
				     MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
				    << 3);
			lp_pause = ((lp_pause &
				     MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
				    << 3);
		}
	} else {
		bnx2x_cl45_read(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_ADV_PAUSE, &ld_pause);
		bnx2x_cl45_read(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG, &lp_pause);
	}
	pause_result = (ld_pause &
			MDIO_AN_REG_ADV_PAUSE_MASK) >> 8;
	pause_result |= (lp_pause &
			 MDIO_AN_REG_ADV_PAUSE_MASK) >> 10;
	DP(NETIF_MSG_LINK, "Ext PHY pause result 0x%x\n", pause_result);
	bnx2x_pause_resolve(vars, pause_result);

}