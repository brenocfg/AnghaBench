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
struct be_dma_mem {int dummy; } ;
struct be_cmd_get_nic_conf_resp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_GET_NIC_CONFIG ; 
 int mgmt_alloc_cmd_data (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 
 int mgmt_exec_nonemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,struct be_cmd_get_nic_conf_resp*,int) ; 

int mgmt_get_nic_conf(struct beiscsi_hba *phba,
		      struct be_cmd_get_nic_conf_resp *nic)
{
	struct be_dma_mem nonemb_cmd;
	int rc;

	rc = mgmt_alloc_cmd_data(phba, &nonemb_cmd,
				 OPCODE_COMMON_ISCSI_NTWK_GET_NIC_CONFIG,
				 sizeof(*nic));
	if (rc)
		return rc;

	return mgmt_exec_nonemb_cmd(phba, &nonemb_cmd, nic, sizeof(*nic));
}