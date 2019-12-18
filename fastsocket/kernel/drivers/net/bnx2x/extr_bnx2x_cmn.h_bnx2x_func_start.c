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
struct bnx2x_func_start_params {int /*<<< orphan*/  gre_tunnel_rss; int /*<<< orphan*/  gre_tunnel_mode; int /*<<< orphan*/  network_cos_mode; int /*<<< orphan*/  sd_vlan_tag; int /*<<< orphan*/  mf_mode; } ;
struct TYPE_2__ {struct bnx2x_func_start_params start; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/  ramrod_flags; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  mf_ov; int /*<<< orphan*/  mf_mode; int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_F_CMD_START ; 
 int /*<<< orphan*/  GRE_INNER_HEADERS_RSS ; 
 int /*<<< orphan*/  IPGRE_TUNNEL ; 
 int /*<<< orphan*/  OVERRIDE_COS ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 

__attribute__((used)) static inline int bnx2x_func_start(struct bnx2x *bp)
{
	struct bnx2x_func_state_params func_params = {NULL};
	struct bnx2x_func_start_params *start_params =
		&func_params.params.start;

	/* Prepare parameters for function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_START;

	/* Function parameters */
	start_params->mf_mode = bp->mf_mode;
	start_params->sd_vlan_tag = bp->mf_ov;
	start_params->network_cos_mode = OVERRIDE_COS;

	start_params->gre_tunnel_mode = IPGRE_TUNNEL;
	start_params->gre_tunnel_rss = GRE_INNER_HEADERS_RSS;

	return bnx2x_func_state_change(bp, &func_params);
}