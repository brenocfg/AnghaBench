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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop {int state; scalar_t__ rc; TYPE_1__* op_p; } ;
struct bnx2x_rx_mode_ramrod_params {int dummy; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vfop_rxmode_state { ____Placeholder_bnx2x_vfop_rxmode_state } bnx2x_vfop_rxmode_state ;
struct TYPE_2__ {struct bnx2x_rx_mode_ramrod_params rx_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
#define  BNX2X_VFOP_RXMODE_CONFIG 129 
#define  BNX2X_VFOP_RXMODE_DONE 128 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VFOP_DONE ; 
 scalar_t__ bnx2x_config_rx_mode (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 
 int /*<<< orphan*/  bnx2x_vfop_finalize (struct bnx2x_virtf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfop_reset_wq (struct bnx2x_virtf*) ; 

__attribute__((used)) static void bnx2x_vfop_rxmode(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	struct bnx2x_rx_mode_ramrod_params *ramrod = &vfop->op_p->rx_mode;
	enum bnx2x_vfop_rxmode_state state = vfop->state;

	bnx2x_vfop_reset_wq(vf);

	if (vfop->rc < 0)
		goto op_err;

	DP(BNX2X_MSG_IOV, "vf[%d] STATE: %d\n", vf->abs_vfid, state);

	switch (state) {
	case BNX2X_VFOP_RXMODE_CONFIG:
		/* next state */
		vfop->state = BNX2X_VFOP_RXMODE_DONE;

		vfop->rc = bnx2x_config_rx_mode(bp, ramrod);
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);
op_err:
		BNX2X_ERR("RXMODE error: rc %d\n", vfop->rc);
op_done:
	case BNX2X_VFOP_RXMODE_DONE:
		bnx2x_vfop_end(bp, vf, vfop);
		return;
	default:
		bnx2x_vfop_default(state);
	}
op_pending:
	return;
}