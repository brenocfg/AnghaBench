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
struct beiscsi_hba {int dummy; } ;
struct be_dma_mem {struct be_cmd_get_def_gateway_req* va; } ;
struct be_cmd_get_def_gateway_resp {int dummy; } ;
struct be_cmd_get_def_gateway_req {int ip_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_GET_DEFAULT_GATEWAY ; 
 int mgmt_alloc_cmd_data (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 
 int mgmt_exec_nonemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,struct be_cmd_get_def_gateway_resp*,int) ; 

int mgmt_get_gateway(struct beiscsi_hba *phba, int ip_type,
		     struct be_cmd_get_def_gateway_resp *gateway)
{
	struct be_cmd_get_def_gateway_req *req;
	struct be_dma_mem nonemb_cmd;
	int rc;

	rc = mgmt_alloc_cmd_data(phba, &nonemb_cmd,
				 OPCODE_COMMON_ISCSI_NTWK_GET_DEFAULT_GATEWAY,
				 sizeof(*gateway));
	if (rc)
		return rc;

	req = nonemb_cmd.va;
	req->ip_type = ip_type;

	return mgmt_exec_nonemb_cmd(phba, &nonemb_cmd, gateway,
				    sizeof(*gateway));
}