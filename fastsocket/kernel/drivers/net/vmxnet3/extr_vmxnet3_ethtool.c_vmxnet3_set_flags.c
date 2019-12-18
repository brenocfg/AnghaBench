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
typedef  int u8 ;
typedef  int u32 ;
struct vmxnet3_adapter {int lro; TYPE_3__* shared; } ;
struct net_device {int features; } ;
struct TYPE_4__ {int /*<<< orphan*/  uptFeatures; } ;
struct TYPE_5__ {TYPE_1__ misc; } ;
struct TYPE_6__ {TYPE_2__ devRead; } ;

/* Variables and functions */
 int ETH_FLAG_LRO ; 
 int NETIF_F_LRO ; 
 int /*<<< orphan*/  UPT1_F_LRO ; 
 int /*<<< orphan*/  VMXNET3_CMD_UPDATE_FEATURE ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
vmxnet3_set_flags(struct net_device *netdev, u32 data) {
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	u8 lro_requested = (data & ETH_FLAG_LRO) == 0 ? 0 : 1;
	u8 lro_present = (netdev->features & NETIF_F_LRO) == 0 ? 0 : 1;
 
	if (lro_requested ^ lro_present) {
		/* toggle the LRO feature*/
		netdev->features ^= NETIF_F_LRO;

		/* Update private LRO flag */
		adapter->lro = lro_requested;

		/* update harware LRO capability accordingly */
		if (lro_requested)
			adapter->shared->devRead.misc.uptFeatures |=
						cpu_to_le64(UPT1_F_LRO);
		else
			adapter->shared->devRead.misc.uptFeatures &=
						cpu_to_le64(~UPT1_F_LRO);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_UPDATE_FEATURE);
	}
	return 0;
}