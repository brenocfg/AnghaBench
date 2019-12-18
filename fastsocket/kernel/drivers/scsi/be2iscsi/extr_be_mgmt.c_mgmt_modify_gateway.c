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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct beiscsi_hba {int dummy; } ;
struct be_dma_mem {struct be_cmd_set_def_gateway_req* va; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  ip_type; } ;
struct be_cmd_set_def_gateway_req {TYPE_1__ ip_addr; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_IPV4 ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_MODIFY_DEFAULT_GATEWAY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mgmt_alloc_cmd_data (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 
 int mgmt_exec_nonemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mgmt_modify_gateway(struct beiscsi_hba *phba, uint8_t *gt_addr,
			       uint32_t gtway_action, uint32_t param_len)
{
	struct be_cmd_set_def_gateway_req *req;
	struct be_dma_mem nonemb_cmd;
	int rt_val;


	rt_val = mgmt_alloc_cmd_data(phba, &nonemb_cmd,
				OPCODE_COMMON_ISCSI_NTWK_MODIFY_DEFAULT_GATEWAY,
				sizeof(*req));
	if (rt_val)
		return rt_val;

	req = nonemb_cmd.va;
	req->action = gtway_action;
	req->ip_addr.ip_type = BE2_IPV4;

	memcpy(req->ip_addr.addr, gt_addr, param_len);

	return mgmt_exec_nonemb_cmd(phba, &nonemb_cmd, NULL, 0);
}