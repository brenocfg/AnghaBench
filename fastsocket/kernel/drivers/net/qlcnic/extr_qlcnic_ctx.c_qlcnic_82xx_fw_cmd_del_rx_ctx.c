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
struct qlcnic_recv_context {int /*<<< orphan*/  state; int /*<<< orphan*/  context_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_1__* pdev; struct qlcnic_recv_context* recv_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_DESTROY_RX_CTX ; 
 int /*<<< orphan*/  QLCNIC_HOST_CTX_STATE_FREED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

void qlcnic_82xx_fw_cmd_del_rx_ctx(struct qlcnic_adapter *adapter)
{
	int err;
	struct qlcnic_cmd_args cmd;
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_RX_CTX);
	cmd.req.arg[1] = recv_ctx->context_id;
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err)
		dev_err(&adapter->pdev->dev,
			"Failed to destroy rx ctx in firmware\n");

	recv_ctx->state = QLCNIC_HOST_CTX_STATE_FREED;
	qlcnic_free_mbx_args(&cmd);
}