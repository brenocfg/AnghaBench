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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2x_rx_mode_ramrod_params {unsigned long ramrod_flags; unsigned long rx_mode_flags; unsigned long rx_accept_flags; unsigned long tx_accept_flags; int /*<<< orphan*/  rdata_mapping; int /*<<< orphan*/  rdata; int /*<<< orphan*/  state; int /*<<< orphan*/ * pstate; int /*<<< orphan*/  func_id; int /*<<< orphan*/ * rx_mode_obj; int /*<<< orphan*/  cl_id; scalar_t__ cid; } ;
struct bnx2x {int /*<<< orphan*/  rx_mode; int /*<<< orphan*/  sp_state; int /*<<< orphan*/  rx_mode_obj; } ;
typedef  int /*<<< orphan*/  ramrod_param ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  BP_FUNC (struct bnx2x*) ; 
 int bnx2x_config_rx_mode (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ; 
 int /*<<< orphan*/  bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnx2x_rx_mode_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rx_mode_rdata ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_set_q_rx_mode(struct bnx2x *bp, u8 cl_id,
			unsigned long rx_mode_flags,
			unsigned long rx_accept_flags,
			unsigned long tx_accept_flags,
			unsigned long ramrod_flags)
{
	struct bnx2x_rx_mode_ramrod_params ramrod_param;
	int rc;

	memset(&ramrod_param, 0, sizeof(ramrod_param));

	/* Prepare ramrod parameters */
	ramrod_param.cid = 0;
	ramrod_param.cl_id = cl_id;
	ramrod_param.rx_mode_obj = &bp->rx_mode_obj;
	ramrod_param.func_id = BP_FUNC(bp);

	ramrod_param.pstate = &bp->sp_state;
	ramrod_param.state = BNX2X_FILTER_RX_MODE_PENDING;

	ramrod_param.rdata = bnx2x_sp(bp, rx_mode_rdata);
	ramrod_param.rdata_mapping = bnx2x_sp_mapping(bp, rx_mode_rdata);

	set_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state);

	ramrod_param.ramrod_flags = ramrod_flags;
	ramrod_param.rx_mode_flags = rx_mode_flags;

	ramrod_param.rx_accept_flags = rx_accept_flags;
	ramrod_param.tx_accept_flags = tx_accept_flags;

	rc = bnx2x_config_rx_mode(bp, &ramrod_param);
	if (rc < 0) {
		BNX2X_ERR("Set rx_mode %d failed\n", bp->rx_mode);
		return rc;
	}

	return 0;
}