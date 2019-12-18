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
struct vmxnet3_adapter {int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_STATE_BIT_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmxnet3_quiesce_dev (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_rq_destroy_all (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_tq_destroy_all (struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_close(struct net_device *netdev)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	/*
	 * Reset_work may be in the middle of resetting the device, wait for its
	 * completion.
	 */
	while (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		msleep(1);

	vmxnet3_quiesce_dev(adapter);

	vmxnet3_rq_destroy_all(adapter);
	vmxnet3_tq_destroy_all(adapter);

	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);


	return 0;
}