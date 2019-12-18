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
struct function_update_data {int tx_switch_suspend_change_flg; int /*<<< orphan*/  echo; int /*<<< orphan*/  tx_switch_suspend; } ;
struct bnx2x_func_switch_update_params {int /*<<< orphan*/  suspend; } ;
struct TYPE_2__ {struct bnx2x_func_switch_update_params switch_update; } ;
struct bnx2x_func_state_params {TYPE_1__ params; struct bnx2x_func_sp_obj* f_obj; } ;
struct bnx2x_func_sp_obj {int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE ; 
 int /*<<< orphan*/  SWITCH_UPDATE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct function_update_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_func_send_switch_update(struct bnx2x *bp,
					struct bnx2x_func_state_params *params)
{
	struct bnx2x_func_sp_obj *o = params->f_obj;
	struct function_update_data *rdata =
		(struct function_update_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	struct bnx2x_func_switch_update_params *switch_update_params =
		&params->params.switch_update;

	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->tx_switch_suspend_change_flg = 1;
	rdata->tx_switch_suspend = switch_update_params->suspend;
	rdata->echo = SWITCH_UPDATE;

	return bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
}