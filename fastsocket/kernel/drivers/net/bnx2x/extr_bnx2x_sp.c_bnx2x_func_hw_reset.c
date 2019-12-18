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
typedef  int u32 ;
struct TYPE_3__ {int reset_phase; } ;
struct TYPE_4__ {TYPE_1__ hw_reset; } ;
struct bnx2x_func_state_params {struct bnx2x_func_sp_obj* f_obj; TYPE_2__ params; } ;
struct bnx2x_func_sp_obj {int /*<<< orphan*/  (* complete_cmd ) (struct bnx2x*,struct bnx2x_func_sp_obj*,int /*<<< orphan*/ ) ;struct bnx2x_func_sp_drv_ops* drv; } ;
struct bnx2x_func_sp_drv_ops {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_HW_RESET ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BP_ABS_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
#define  FW_MSG_CODE_DRV_UNLOAD_COMMON 130 
#define  FW_MSG_CODE_DRV_UNLOAD_FUNCTION 129 
#define  FW_MSG_CODE_DRV_UNLOAD_PORT 128 
 int /*<<< orphan*/  bnx2x_func_reset_cmn (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  bnx2x_func_reset_func (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  bnx2x_func_reset_port (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_func_sp_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bnx2x_func_hw_reset(struct bnx2x *bp,
				      struct bnx2x_func_state_params *params)
{
	u32 reset_phase = params->params.hw_reset.reset_phase;
	struct bnx2x_func_sp_obj *o = params->f_obj;
	const struct bnx2x_func_sp_drv_ops *drv = o->drv;

	DP(BNX2X_MSG_SP, "function %d  reset_phase %x\n", BP_ABS_FUNC(bp),
			 reset_phase);

	switch (reset_phase) {
	case FW_MSG_CODE_DRV_UNLOAD_COMMON:
		bnx2x_func_reset_cmn(bp, drv);
		break;
	case FW_MSG_CODE_DRV_UNLOAD_PORT:
		bnx2x_func_reset_port(bp, drv);
		break;
	case FW_MSG_CODE_DRV_UNLOAD_FUNCTION:
		bnx2x_func_reset_func(bp, drv);
		break;
	default:
		BNX2X_ERR("Unknown reset_phase (0x%x) from MCP\n",
			   reset_phase);
		break;
	}

	/* Complete the command immediately: no ramrods have been sent. */
	o->complete_cmd(bp, o, BNX2X_F_CMD_HW_RESET);

	return 0;
}