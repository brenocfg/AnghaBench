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
typedef  int u32 ;
struct vmxnet3_adapter {int link_speed; int num_tx_queues; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  netdev; int /*<<< orphan*/  cmd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_GET_LINK ; 
 int VMXNET3_READ_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vmxnet3_tq_start (int /*<<< orphan*/ *,struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_tq_stop (int /*<<< orphan*/ *,struct vmxnet3_adapter*) ; 

__attribute__((used)) static void
vmxnet3_check_link(struct vmxnet3_adapter *adapter, bool affectTxQueue)
{
	u32 ret;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD, VMXNET3_CMD_GET_LINK);
	ret = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	adapter->link_speed = ret >> 16;
	if (ret & 1) { /* Link is up. */
		netdev_info(adapter->netdev, "NIC Link is Up %d Mbps\n",
			    adapter->link_speed);
		netif_carrier_on(adapter->netdev);

		if (affectTxQueue) {
			for (i = 0; i < adapter->num_tx_queues; i++)
				vmxnet3_tq_start(&adapter->tx_queue[i],
						 adapter);
		}
	} else {
		netdev_info(adapter->netdev, "NIC Link is Down\n");
		netif_carrier_off(adapter->netdev);

		if (affectTxQueue) {
			for (i = 0; i < adapter->num_tx_queues; i++)
				vmxnet3_tq_stop(&adapter->tx_queue[i], adapter);
		}
	}
}