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
typedef  size_t u8 ;
struct link_vars {int link_up; scalar_t__ line_speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  flow_ctrl; } ;
struct link_params {scalar_t__* req_line_speed; scalar_t__ loopback_mode; size_t num_phys; int port; struct bnx2x_phy* phy; struct bnx2x* bp; } ;
struct bnx2x_phy {int flags; int /*<<< orphan*/  (* config_loopback ) (struct bnx2x_phy*,struct link_params*) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_NONE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 size_t EXT_PHY1 ; 
 int FLAGS_WC_DUAL_MODE ; 
 size_t INT_PHY ; 
 int /*<<< orphan*/  LED_MODE_OPER ; 
 scalar_t__ LOOPBACK_XGXS ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 scalar_t__ SPEED_20000 ; 
 scalar_t__ USES_WARPCORE (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_bmac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_emac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_emac_program (struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_link_initialize (struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_set_led (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_umac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_xgxs_deassert (struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_xmac_enable (struct link_params*,struct link_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_init_xgxs_loopback(struct link_params *params,
				     struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	struct bnx2x_phy *int_phy = &params->phy[INT_PHY];
	vars->link_up = 1;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->duplex = DUPLEX_FULL;
	if (params->req_line_speed[0] == SPEED_1000)
		vars->line_speed = SPEED_1000;
	else if ((params->req_line_speed[0] == SPEED_20000) ||
		 (int_phy->flags & FLAGS_WC_DUAL_MODE))
		vars->line_speed = SPEED_20000;
	else
		vars->line_speed = SPEED_10000;

	if (!USES_WARPCORE(bp))
		bnx2x_xgxs_deassert(params);
	bnx2x_link_initialize(params, vars);

	if (params->req_line_speed[0] == SPEED_1000) {
		if (USES_WARPCORE(bp))
			bnx2x_umac_enable(params, vars, 0);
		else {
			bnx2x_emac_program(params, vars);
			bnx2x_emac_enable(params, vars, 0);
		}
	} else {
		if (USES_WARPCORE(bp))
			bnx2x_xmac_enable(params, vars, 0);
		else
			bnx2x_bmac_enable(params, vars, 0, 1);
	}

	if (params->loopback_mode == LOOPBACK_XGXS) {
		/* Set 10G XGXS loopback */
		int_phy->config_loopback(int_phy, params);
	} else {
		/* Set external phy loopback */
		u8 phy_index;
		for (phy_index = EXT_PHY1;
		      phy_index < params->num_phys; phy_index++)
			if (params->phy[phy_index].config_loopback)
				params->phy[phy_index].config_loopback(
					&params->phy[phy_index],
					params);
	}
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);

	bnx2x_set_led(params, vars, LED_MODE_OPER, vars->line_speed);
}