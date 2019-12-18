#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u64 ;
struct vmxnet3_adapter {int num_tx_queues; TYPE_4__* rx_queue; TYPE_3__* rqd_start; TYPE_2__* tx_queue; TYPE_1__* tqd_start; int /*<<< orphan*/  cmd_lock; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_15__ {int offset; } ;
struct TYPE_14__ {int /*<<< orphan*/  stats; } ;
struct TYPE_13__ {int /*<<< orphan*/  stats; } ;
struct TYPE_12__ {int /*<<< orphan*/  stats; } ;
struct TYPE_11__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  VMXNET3_CMD_GET_STATS ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_5__* vmxnet3_global_stats ; 
 TYPE_5__* vmxnet3_rq_dev_stats ; 
 TYPE_5__* vmxnet3_rq_driver_stats ; 
 TYPE_5__* vmxnet3_tq_dev_stats ; 
 TYPE_5__* vmxnet3_tq_driver_stats ; 

__attribute__((used)) static void
vmxnet3_get_ethtool_stats(struct net_device *netdev,
			  struct ethtool_stats *stats, u64  *buf)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	unsigned long flags;
	u8 *base;
	int i;
	int j = 0;

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD, VMXNET3_CMD_GET_STATS);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	/* this does assume each counter is 64-bit wide */
	for (j = 0; j < adapter->num_tx_queues; j++) {
		base = (u8 *)&adapter->tqd_start[j].stats;
		*buf++ = (u64)j;
		for (i = 1; i < ARRAY_SIZE(vmxnet3_tq_dev_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_tq_dev_stats[i].offset);

		base = (u8 *)&adapter->tx_queue[j].stats;
		for (i = 0; i < ARRAY_SIZE(vmxnet3_tq_driver_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_tq_driver_stats[i].offset);
	}

	for (j = 0; j < adapter->num_tx_queues; j++) {
		base = (u8 *)&adapter->rqd_start[j].stats;
		*buf++ = (u64) j;
		for (i = 1; i < ARRAY_SIZE(vmxnet3_rq_dev_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_rq_dev_stats[i].offset);

		base = (u8 *)&adapter->rx_queue[j].stats;
		for (i = 0; i < ARRAY_SIZE(vmxnet3_rq_driver_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_rq_driver_stats[i].offset);
	}

	base = (u8 *)adapter;
	for (i = 0; i < ARRAY_SIZE(vmxnet3_global_stats); i++)
		*buf++ = *(u64 *)(base + vmxnet3_global_stats[i].offset);
}