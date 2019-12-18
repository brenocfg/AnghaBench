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
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_down (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_fdir_filter_exit (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_free_all_rx_resources (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_free_all_tx_resources (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_free_irq (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_stop (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_release_hw_control (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_close(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

#ifdef CONFIG_IXGBE_PTP
	ixgbe_ptp_stop(adapter);
#endif

	ixgbe_down(adapter);
	ixgbe_free_irq(adapter);

	ixgbe_fdir_filter_exit(adapter);

	ixgbe_free_all_tx_resources(adapter);
	ixgbe_free_all_rx_resources(adapter);

	ixgbe_release_hw_control(adapter);

	return 0;
}