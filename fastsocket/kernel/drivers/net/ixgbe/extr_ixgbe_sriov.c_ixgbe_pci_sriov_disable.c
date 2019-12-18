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
typedef  scalar_t__ u32 ;
struct pci_dev {int dummy; } ;
struct ixgbe_adapter {scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ IXGBE_FLAG_VMDQ_ENABLED ; 
 int ixgbe_disable_sriov (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_sriov_reinit (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int ixgbe_pci_sriov_disable(struct pci_dev *dev)
{
	struct ixgbe_adapter *adapter = pci_get_drvdata(dev);
	int err;
	u32 current_flags = adapter->flags;

	err = ixgbe_disable_sriov(adapter);

	/* Only reinit if no error and state changed */
	if (!err && current_flags != adapter->flags) {
		/* ixgbe_disable_sriov() doesn't clear VMDQ flag */
		adapter->flags &= ~IXGBE_FLAG_VMDQ_ENABLED;
#ifdef CONFIG_PCI_IOV
		ixgbe_sriov_reinit(adapter);
#endif
	}

	return err;
}