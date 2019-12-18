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
struct flow_control_configuration {int /*<<< orphan*/ * traffic_type_to_priority_cos; int /*<<< orphan*/  dont_add_pri_0_en; int /*<<< orphan*/  dcb_version; int /*<<< orphan*/  dcb_enabled; } ;
struct bnx2x_func_tx_start_params {int /*<<< orphan*/ * traffic_type_to_priority_cos; int /*<<< orphan*/  dont_add_pri_0_en; int /*<<< orphan*/  dcb_version; int /*<<< orphan*/  dcb_enabled; } ;
struct TYPE_2__ {struct bnx2x_func_tx_start_params tx_start; } ;
struct bnx2x_func_state_params {TYPE_1__ params; struct bnx2x_func_sp_obj* f_obj; } ;
struct bnx2x_func_sp_obj {int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_START_TRAFFIC ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct flow_control_configuration*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_func_send_tx_start(struct bnx2x *bp,
				       struct bnx2x_func_state_params *params)
{
	struct bnx2x_func_sp_obj *o = params->f_obj;
	struct flow_control_configuration *rdata =
		(struct flow_control_configuration *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	struct bnx2x_func_tx_start_params *tx_start_params =
		&params->params.tx_start;
	int i;

	memset(rdata, 0, sizeof(*rdata));

	rdata->dcb_enabled = tx_start_params->dcb_enabled;
	rdata->dcb_version = tx_start_params->dcb_version;
	rdata->dont_add_pri_0_en = tx_start_params->dont_add_pri_0_en;

	for (i = 0; i < ARRAY_SIZE(rdata->traffic_type_to_priority_cos); i++)
		rdata->traffic_type_to_priority_cos[i] =
			tx_start_params->traffic_type_to_priority_cos[i];

	return bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_START_TRAFFIC, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
}