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
struct vmxnet3_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  jumbo_frame; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int VMXNET3_MAX_MTU ; 
 int VMXNET3_MIN_MTU ; 
 int /*<<< orphan*/  VMXNET3_STATE_BIT_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vmxnet3_activate_dev (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_adjust_rx_ring_size (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_force_close (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_quiesce_dev (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_reset_dev (struct vmxnet3_adapter*) ; 
 int vmxnet3_rq_create_all (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_rq_destroy_all (struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	int err = 0;

	if (new_mtu < VMXNET3_MIN_MTU || new_mtu > VMXNET3_MAX_MTU)
		return -EINVAL;

	if (new_mtu > 1500 && !adapter->jumbo_frame)
		return -EINVAL;

	netdev->mtu = new_mtu;

	/*
	 * Reset_work may be in the middle of resetting the device, wait for its
	 * completion.
	 */
	while (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		msleep(1);

	if (netif_running(netdev)) {
		vmxnet3_quiesce_dev(adapter);
		vmxnet3_reset_dev(adapter);

		/* we need to re-create the rx queue based on the new mtu */
		vmxnet3_rq_destroy_all(adapter);
		vmxnet3_adjust_rx_ring_size(adapter);
		err = vmxnet3_rq_create_all(adapter);
		if (err) {
			netdev_err(netdev,
				   "failed to re-create rx queues, "
				   " error %d. Closing it.\n", err);
			goto out;
		}

		err = vmxnet3_activate_dev(adapter);
		if (err) {
			netdev_err(netdev,
				   "failed to re-activate, error %d. "
				   "Closing it\n", err);
			goto out;
		}
	}

out:
	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
	if (err)
		vmxnet3_force_close(adapter);

	return err;
}