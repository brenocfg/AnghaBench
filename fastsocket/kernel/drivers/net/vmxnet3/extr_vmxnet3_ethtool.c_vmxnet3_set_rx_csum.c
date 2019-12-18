#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vmxnet3_adapter {scalar_t__ rxcsum; int /*<<< orphan*/  cmd_lock; TYPE_1__* shared; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  uptFeatures; } ;
struct TYPE_6__ {TYPE_2__ misc; } ;
struct TYPE_4__ {TYPE_3__ devRead; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPT1_F_RXCSUM ; 
 int /*<<< orphan*/  VMXNET3_CMD_UPDATE_FEATURE ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
vmxnet3_set_rx_csum(struct net_device *netdev, u32 val)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	unsigned long flags;

	if (adapter->rxcsum != val) {
		adapter->rxcsum = val;
		if (netif_running(netdev)) {
			if (val)
				adapter->shared->devRead.misc.uptFeatures |=
				UPT1_F_RXCSUM;
			else
				adapter->shared->devRead.misc.uptFeatures &=
				~UPT1_F_RXCSUM;

			spin_lock_irqsave(&adapter->cmd_lock, flags);
			VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
					       VMXNET3_CMD_UPDATE_FEATURE);
			spin_unlock_irqrestore(&adapter->cmd_lock, flags);
		}
	}
	return 0;
}