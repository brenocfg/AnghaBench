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
struct beiscsi_hba {int /*<<< orphan*/  interface_handle; } ;
struct be_dma_mem {struct be_cmd_get_if_info_req* va; } ;
struct be_cmd_get_if_info_resp {int dummy; } ;
struct be_cmd_get_if_info_req {int ip_type; int /*<<< orphan*/  interface_hndl; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO ; 
 int mgmt_alloc_cmd_data (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 
 int mgmt_exec_nonemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,struct be_cmd_get_if_info_resp*,int) ; 
 scalar_t__ mgmt_get_all_if_id (struct beiscsi_hba*) ; 

int mgmt_get_if_info(struct beiscsi_hba *phba, int ip_type,
		     struct be_cmd_get_if_info_resp *if_info)
{
	struct be_cmd_get_if_info_req *req;
	struct be_dma_mem nonemb_cmd;
	int rc;

	if (mgmt_get_all_if_id(phba))
		return -EIO;

	rc = mgmt_alloc_cmd_data(phba, &nonemb_cmd,
				 OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO,
				 sizeof(*if_info));
	if (rc)
		return rc;

	req = nonemb_cmd.va;
	req->interface_hndl = phba->interface_handle;
	req->ip_type = ip_type;

	return mgmt_exec_nonemb_cmd(phba, &nonemb_cmd, if_info,
				    sizeof(*if_info));
}