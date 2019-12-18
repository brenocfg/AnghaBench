#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int num; int /*<<< orphan*/  arg; } ;
struct TYPE_6__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_4__ rsp; TYPE_2__ req; } ;
struct qlcnic_adapter {int portnum; TYPE_3__* recv_ctx; TYPE_1__* tx_ring; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int context_id; } ;
struct TYPE_5__ {int ctx_id; } ;

/* Variables and functions */
 int BIT_1 ; 
 int BIT_2 ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_STATISTICS ; 
 int QLC_83XX_MAC_STAT_REGS ; 
 int QLC_83XX_RX_STAT_REGS ; 
 int /*<<< orphan*/  QLC_83XX_STAT_MAC ; 
 int /*<<< orphan*/  QLC_83XX_STAT_RX ; 
 int /*<<< orphan*/  QLC_83XX_STAT_TX ; 
 int QLC_83XX_TX_STAT_REGS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/ * qlcnic_83xx_fill_stats (struct qlcnic_adapter*,struct qlcnic_cmd_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 

void qlcnic_83xx_get_stats(struct qlcnic_adapter *adapter, u64 *data)
{
	struct qlcnic_cmd_args cmd;
	struct net_device *netdev = adapter->netdev;
	int ret = 0;

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_STATISTICS);
	/* Get Tx stats */
	cmd.req.arg[1] = BIT_1 | (adapter->tx_ring->ctx_id << 16);
	cmd.rsp.num = QLC_83XX_TX_STAT_REGS;
	data = qlcnic_83xx_fill_stats(adapter, &cmd, data,
				      QLC_83XX_STAT_TX, &ret);
	if (ret) {
		netdev_err(netdev, "Error getting Tx stats\n");
		goto out;
	}
	/* Get MAC stats */
	cmd.req.arg[1] = BIT_2 | (adapter->portnum << 16);
	cmd.rsp.num = QLC_83XX_MAC_STAT_REGS;
	memset(cmd.rsp.arg, 0, sizeof(u32) * cmd.rsp.num);
	data = qlcnic_83xx_fill_stats(adapter, &cmd, data,
				      QLC_83XX_STAT_MAC, &ret);
	if (ret) {
		netdev_err(netdev, "Error getting MAC stats\n");
		goto out;
	}
	/* Get Rx stats */
	cmd.req.arg[1] = adapter->recv_ctx->context_id << 16;
	cmd.rsp.num = QLC_83XX_RX_STAT_REGS;
	memset(cmd.rsp.arg, 0, sizeof(u32) * cmd.rsp.num);
	data = qlcnic_83xx_fill_stats(adapter, &cmd, data,
				      QLC_83XX_STAT_RX, &ret);
	if (ret)
		netdev_err(netdev, "Error getting Rx stats\n");
out:
	qlcnic_free_mbx_args(&cmd);
}