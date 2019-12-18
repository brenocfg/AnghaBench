#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct link_vars {int link_up; int /*<<< orphan*/  phy_flags; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  duplex; scalar_t__ line_speed; } ;
struct link_params {int port; TYPE_1__* phy; scalar_t__* req_line_speed; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* config_loopback ) (TYPE_1__*,struct link_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_NONE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 size_t INT_PHY ; 
 int /*<<< orphan*/  MAC_TYPE_XMAC ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  PHY_XGXS_FLAG ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_set_aer_mmd (struct link_params*,TYPE_1__*) ; 
 int /*<<< orphan*/  bnx2x_warpcore_reset_lane (struct bnx2x*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_xmac_enable (struct link_params*,struct link_vars*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_init_xmac_loopback(struct link_params *params,
				     struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	vars->link_up = 1;
	if (!params->req_line_speed[0])
		vars->line_speed = SPEED_10000;
	else
		vars->line_speed = params->req_line_speed[0];
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_XMAC;
	vars->phy_flags = PHY_XGXS_FLAG;
	/* Set WC to loopback mode since link is required to provide clock
	 * to the XMAC in 20G mode
	 */
	bnx2x_set_aer_mmd(params, &params->phy[0]);
	bnx2x_warpcore_reset_lane(bp, &params->phy[0], 0);
	params->phy[INT_PHY].config_loopback(
			&params->phy[INT_PHY],
			params);

	bnx2x_xmac_enable(params, vars, 1);
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
}