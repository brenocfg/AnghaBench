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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {scalar_t__ reg_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_addr; } ;
struct ixgbe_adapter {int flags; TYPE_1__ hw; int /*<<< orphan*/  ixgbe_ieee_ets; int /*<<< orphan*/  ixgbe_ieee_pfc; int /*<<< orphan*/  service_task; int /*<<< orphan*/  state; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IXGBE_DCA_CTRL ; 
 int IXGBE_FLAG_DCA_ENABLED ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dca_remove_requester (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dev_info (char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_clear_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_dbg_adapter_exit (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_del_sanmac_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ixgbe_disable_sriov (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_release_hw_control (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_sysfs_exit (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ max_vfs ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_selected_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ixgbe_remove(struct pci_dev *pdev)
{
	struct ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;

	ixgbe_dbg_adapter_exit(adapter);

	set_bit(__IXGBE_DOWN, &adapter->state);
	cancel_work_sync(&adapter->service_task);


#ifdef CONFIG_IXGBE_DCA
	if (adapter->flags & IXGBE_FLAG_DCA_ENABLED) {
		adapter->flags &= ~IXGBE_FLAG_DCA_ENABLED;
		dca_remove_requester(&pdev->dev);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL, 1);
	}

#endif
#ifdef CONFIG_IXGBE_HWMON
	ixgbe_sysfs_exit(adapter);
#endif /* CONFIG_IXGBE_HWMON */

	/* remove the added san mac */
	ixgbe_del_sanmac_netdev(netdev);

	if (netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(netdev);

#ifdef CONFIG_PCI_IOV
	/*
	 * Only disable SR-IOV on unload if the user specified the now
	 * deprecated max_vfs module parameter.
	 */
	if (max_vfs)
		ixgbe_disable_sriov(adapter);
#endif
	ixgbe_clear_interrupt_scheme(adapter);

	ixgbe_release_hw_control(adapter);

#ifdef CONFIG_DCB
	kfree(adapter->ixgbe_ieee_pfc);
	kfree(adapter->ixgbe_ieee_ets);

#endif
	iounmap(adapter->hw.hw_addr);
	pci_release_selected_regions(pdev, pci_select_bars(pdev,
				     IORESOURCE_MEM));

	e_dev_info("complete\n");

	free_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
}