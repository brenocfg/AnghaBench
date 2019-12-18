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
struct TYPE_3__ {int load_phase; } ;
struct TYPE_4__ {TYPE_1__ hw_init; } ;
struct bnx2x_func_state_params {struct bnx2x_func_sp_obj* f_obj; TYPE_2__ params; } ;
struct bnx2x_func_sp_obj {int /*<<< orphan*/  (* complete_cmd ) (struct bnx2x*,struct bnx2x_func_sp_obj*,int /*<<< orphan*/ ) ;struct bnx2x_func_sp_drv_ops* drv; } ;
struct bnx2x_func_sp_drv_ops {int (* gunzip_init ) (struct bnx2x*) ;int (* init_fw ) (struct bnx2x*) ;int /*<<< orphan*/  (* gunzip_end ) (struct bnx2x*) ;} ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_HW_INIT ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BP_ABS_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  FW_MSG_CODE_DRV_LOAD_COMMON 131 
#define  FW_MSG_CODE_DRV_LOAD_COMMON_CHIP 130 
#define  FW_MSG_CODE_DRV_LOAD_FUNCTION 129 
#define  FW_MSG_CODE_DRV_LOAD_PORT 128 
 int bnx2x_func_init_cmn (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int bnx2x_func_init_cmn_chip (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int bnx2x_func_init_func (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int bnx2x_func_init_port (struct bnx2x*,struct bnx2x_func_sp_drv_ops const*) ; 
 int stub1 (struct bnx2x*) ; 
 int stub2 (struct bnx2x*) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x*) ; 
 int /*<<< orphan*/  stub4 (struct bnx2x*,struct bnx2x_func_sp_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_func_hw_init(struct bnx2x *bp,
			      struct bnx2x_func_state_params *params)
{
	u32 load_code = params->params.hw_init.load_phase;
	struct bnx2x_func_sp_obj *o = params->f_obj;
	const struct bnx2x_func_sp_drv_ops *drv = o->drv;
	int rc = 0;

	DP(BNX2X_MSG_SP, "function %d  load_code %x\n",
			 BP_ABS_FUNC(bp), load_code);

	/* Prepare buffers for unzipping the FW */
	rc = drv->gunzip_init(bp);
	if (rc)
		return rc;

	/* Prepare FW */
	rc = drv->init_fw(bp);
	if (rc) {
		BNX2X_ERR("Error loading firmware\n");
		goto init_err;
	}

	/* Handle the beginning of COMMON_XXX pases separately... */
	switch (load_code) {
	case FW_MSG_CODE_DRV_LOAD_COMMON_CHIP:
		rc = bnx2x_func_init_cmn_chip(bp, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_COMMON:
		rc = bnx2x_func_init_cmn(bp, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_PORT:
		rc = bnx2x_func_init_port(bp, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_FUNCTION:
		rc = bnx2x_func_init_func(bp, drv);
		if (rc)
			goto init_err;

		break;
	default:
		BNX2X_ERR("Unknown load_code (0x%x) from MCP\n", load_code);
		rc = -EINVAL;
	}

init_err:
	drv->gunzip_end(bp);

	/* In case of success, complete the command immediately: no ramrods
	 * have been sent.
	 */
	if (!rc)
		o->complete_cmd(bp, o, BNX2X_F_CMD_HW_INIT);

	return rc;
}