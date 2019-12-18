#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct qlcnic_nic_intr_coalesce {int type; int rx_time_us; int rx_packets; int tx_time_us; int tx_packets; int flag; } ;
struct TYPE_9__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_4__ req; } ;
struct qlcnic_adapter {TYPE_5__* pdev; TYPE_3__* tx_ring; TYPE_2__* recv_ctx; TYPE_1__* ahw; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int ctx_id; } ;
struct TYPE_7__ {scalar_t__ state; int context_id; } ;
struct TYPE_6__ {struct qlcnic_nic_intr_coalesce coal; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_CONFIG_INTR_COAL ; 
 scalar_t__ QLCNIC_HOST_CTX_STATE_FREED ; 
 int QLCNIC_INTR_COAL_TYPE_RX ; 
 int QLCNIC_INTR_COAL_TYPE_TX ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

void qlcnic_83xx_config_intr_coal(struct qlcnic_adapter *adapter)
{
	int err;
	u16 temp;
	struct qlcnic_cmd_args cmd;
	struct qlcnic_nic_intr_coalesce *coal = &adapter->ahw->coal;

	if (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		return;

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_INTR_COAL);
	if (coal->type == QLCNIC_INTR_COAL_TYPE_RX) {
		temp = adapter->recv_ctx->context_id;
		cmd.req.arg[1] = QLCNIC_INTR_COAL_TYPE_RX | temp << 16;
		temp = coal->rx_time_us;
		cmd.req.arg[2] = coal->rx_packets | temp << 16;
	} else if (coal->type == QLCNIC_INTR_COAL_TYPE_TX) {
		temp = adapter->tx_ring->ctx_id;
		cmd.req.arg[1] = QLCNIC_INTR_COAL_TYPE_TX | temp << 16;
		temp = coal->tx_time_us;
		cmd.req.arg[2] = coal->tx_packets | temp << 16;
	}
	cmd.req.arg[3] = coal->flag;
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err != QLCNIC_RCODE_SUCCESS)
		dev_info(&adapter->pdev->dev,
			 "Failed to send interrupt coalescence parameters\n");
	qlcnic_free_mbx_args(&cmd);
}