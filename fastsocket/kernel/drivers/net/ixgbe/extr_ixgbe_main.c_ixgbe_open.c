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
struct net_device {int dummy; } ;
struct ixgbe_adapter {int num_rx_pools; int num_tx_queues; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __IXGBE_TESTING ; 
 int /*<<< orphan*/  ixgbe_configure (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_free_all_rx_resources (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_free_all_tx_resources (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_init (struct ixgbe_adapter*) ; 
 int ixgbe_request_irq (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_reset (struct ixgbe_adapter*) ; 
 int ixgbe_setup_all_rx_resources (struct ixgbe_adapter*) ; 
 int ixgbe_setup_all_tx_resources (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_up_complete (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_open(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	int err;

	/* disallow open during test */
	if (test_bit(__IXGBE_TESTING, &adapter->state))
		return -EBUSY;

	netif_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = ixgbe_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = ixgbe_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	ixgbe_configure(adapter);

	err = ixgbe_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* Notify the stack of the actual queue counts. */
	netif_set_real_num_tx_queues(netdev,
				     adapter->num_rx_pools > 1 ? 1 :
				     adapter->num_tx_queues);

#ifdef CONFIG_IXGBE_PTP
	ixgbe_ptp_init(adapter);
#endif /* CONFIG_IXGBE_PTP*/

	ixgbe_up_complete(adapter);

	return 0;

err_req_irq:
	ixgbe_free_all_rx_resources(adapter);
err_setup_rx:
	ixgbe_free_all_tx_resources(adapter);
err_setup_tx:
	ixgbe_reset(adapter);

	return err;
}