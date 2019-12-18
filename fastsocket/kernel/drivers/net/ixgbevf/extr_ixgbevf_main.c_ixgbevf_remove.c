#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net_device {scalar_t__ reg_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_addr; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; TYPE_1__ hw; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hw_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_clear_interrupt_scheme (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset_interrupt_capability (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ixgbevf_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);

	set_bit(__IXGBEVF_DOWN, &adapter->state);

	del_timer_sync(&adapter->watchdog_timer);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchdog_task);

	if (netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(netdev);

	ixgbevf_clear_interrupt_scheme(adapter);
	ixgbevf_reset_interrupt_capability(adapter);

	iounmap(adapter->hw.hw_addr);
	pci_release_regions(pdev);

	hw_dbg(&adapter->hw, "Remove complete\n");

	kfree(adapter->tx_ring);
	kfree(adapter->rx_ring);

	free_netdev(netdev);

	pci_disable_device(pdev);
}