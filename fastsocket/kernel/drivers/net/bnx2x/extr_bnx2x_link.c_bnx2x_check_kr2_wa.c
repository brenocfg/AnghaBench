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
typedef  int u16 ;
struct link_vars {scalar_t__ check_kr2_recovery_cnt; int link_attr_sync; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int LINK_ATTR_SYNC_KR2_ENABLE ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG2 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_disable_kr2 (struct link_params*,struct link_vars*,struct bnx2x_phy*) ; 
 int bnx2x_get_warpcore_lane (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_kr2_recovery (struct link_params*,struct link_vars*,struct bnx2x_phy*) ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,struct bnx2x_phy*) ; 
 int bnx2x_warpcore_get_sigdet (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_warpcore_restart_AN_KR (struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_check_kr2_wa(struct link_params *params,
			       struct link_vars *vars,
			       struct bnx2x_phy *phy)
{
	struct bnx2x *bp = params->bp;
	u16 base_page, next_page, not_kr2_device, lane;
	int sigdet;

	/* Once KR2 was disabled, wait 5 seconds before checking KR2 recovery
	 * Since some switches tend to reinit the AN process and clear the
	 * the advertised BP/NP after ~2 seconds causing the KR2 to be disabled
	 * and recovered many times
	 */
	if (vars->check_kr2_recovery_cnt > 0) {
		vars->check_kr2_recovery_cnt--;
		return;
	}

	sigdet = bnx2x_warpcore_get_sigdet(phy, params);
	if (!sigdet) {
		if (!(vars->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) {
			bnx2x_kr2_recovery(params, vars, phy);
			DP(NETIF_MSG_LINK, "No sigdet\n");
		}
		return;
	}

	lane = bnx2x_get_warpcore_lane(phy, params);
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, lane);
	bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
			MDIO_AN_REG_LP_AUTO_NEG, &base_page);
	bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
			MDIO_AN_REG_LP_AUTO_NEG2, &next_page);
	bnx2x_set_aer_mmd(params, phy);

	/* CL73 has not begun yet */
	if (base_page == 0) {
		if (!(vars->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) {
			bnx2x_kr2_recovery(params, vars, phy);
			DP(NETIF_MSG_LINK, "No BP\n");
		}
		return;
	}

	/* In case NP bit is not set in the BasePage, or it is set,
	 * but only KX is advertised, declare this link partner as non-KR2
	 * device.
	 */
	not_kr2_device = (((base_page & 0x8000) == 0) ||
			  (((base_page & 0x8000) &&
			    ((next_page & 0xe0) == 0x2))));

	/* In case KR2 is already disabled, check if we need to re-enable it */
	if (!(vars->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) {
		if (!not_kr2_device) {
			DP(NETIF_MSG_LINK, "BP=0x%x, NP=0x%x\n", base_page,
			   next_page);
			bnx2x_kr2_recovery(params, vars, phy);
		}
		return;
	}
	/* KR2 is enabled, but not KR2 device */
	if (not_kr2_device) {
		/* Disable KR2 on both lanes */
		DP(NETIF_MSG_LINK, "BP=0x%x, NP=0x%x\n", base_page, next_page);
		bnx2x_disable_kr2(params, vars, phy);
		/* Restart AN on leading lane */
		bnx2x_warpcore_restart_AN_KR(phy, params);
		return;
	}
}