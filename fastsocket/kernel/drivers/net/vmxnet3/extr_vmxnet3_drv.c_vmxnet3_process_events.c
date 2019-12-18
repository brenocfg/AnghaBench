#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/  work; TYPE_6__* rqd_start; TYPE_4__* netdev; TYPE_3__* tqd_start; int /*<<< orphan*/  cmd_lock; TYPE_1__* shared; } ;
struct TYPE_11__ {int error; scalar_t__ stopped; } ;
struct TYPE_12__ {TYPE_5__ status; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  error; scalar_t__ stopped; } ;
struct TYPE_9__ {TYPE_2__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  ecr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_GET_QUEUE_STATUS ; 
 int VMXNET3_ECR_LINK ; 
 int VMXNET3_ECR_RQERR ; 
 int VMXNET3_ECR_TQERR ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vmxnet3_ack_events (struct vmxnet3_adapter*,int) ; 
 int /*<<< orphan*/  vmxnet3_check_link (struct vmxnet3_adapter*,int) ; 

__attribute__((used)) static void
vmxnet3_process_events(struct vmxnet3_adapter *adapter)
{
	int i;
	unsigned long flags;
	u32 events = le32_to_cpu(adapter->shared->ecr);
	if (!events)
		return;

	vmxnet3_ack_events(adapter, events);

	/* Check if link state has changed */
	if (events & VMXNET3_ECR_LINK)
		vmxnet3_check_link(adapter, true);

	/* Check if there is an error on xmit/recv queues */
	if (events & (VMXNET3_ECR_TQERR | VMXNET3_ECR_RQERR)) {
		spin_lock_irqsave(&adapter->cmd_lock, flags);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_QUEUE_STATUS);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);

		for (i = 0; i < adapter->num_tx_queues; i++)
			if (adapter->tqd_start[i].status.stopped)
				dev_err(&adapter->netdev->dev,
					"%s: tq[%d] error 0x%x\n",
					adapter->netdev->name, i, le32_to_cpu(
					adapter->tqd_start[i].status.error));
		for (i = 0; i < adapter->num_rx_queues; i++)
			if (adapter->rqd_start[i].status.stopped)
				dev_err(&adapter->netdev->dev,
					"%s: rq[%d] error 0x%x\n",
					adapter->netdev->name, i,
					adapter->rqd_start[i].status.error);

		schedule_work(&adapter->work);
	}
}