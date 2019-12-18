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
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LSD (int /*<<< orphan*/ ) ; 
 int MSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_TEMP_HDR ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int __qlcnic_fw_cmd_get_minidump_temp(struct qlcnic_adapter *adapter,
					     u32 *buffer, u32 temp_size)
{
	int err = 0, i;
	void *tmp_addr;
	__le32 *tmp_buf;
	struct qlcnic_cmd_args cmd;
	dma_addr_t tmp_addr_t = 0;

	tmp_addr = dma_alloc_coherent(&adapter->pdev->dev, temp_size,
				      &tmp_addr_t, GFP_KERNEL);
	if (!tmp_addr) {
		dev_err(&adapter->pdev->dev,
			"Can't get memory for FW dump template\n");
		return -ENOMEM;
	}

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_TEMP_HDR)) {
		err = -ENOMEM;
		goto free_mem;
	}

	cmd.req.arg[1] = LSD(tmp_addr_t);
	cmd.req.arg[2] = MSD(tmp_addr_t);
	cmd.req.arg[3] = temp_size;
	err = qlcnic_issue_cmd(adapter, &cmd);

	tmp_buf = tmp_addr;
	if (err == QLCNIC_RCODE_SUCCESS) {
		for (i = 0; i < temp_size / sizeof(u32); i++)
			*buffer++ = __le32_to_cpu(*tmp_buf++);
	}

	qlcnic_free_mbx_args(&cmd);

free_mem:
	dma_free_coherent(&adapter->pdev->dev, temp_size, tmp_addr, tmp_addr_t);

	return err;
}