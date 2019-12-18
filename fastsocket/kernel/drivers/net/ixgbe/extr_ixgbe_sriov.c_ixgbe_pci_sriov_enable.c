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
struct pci_dev {int dummy; } ;
struct ixgbe_adapter {int num_vfs; } ;

/* Variables and functions */
 int EPERM ; 
 int __ixgbe_enable_sriov (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  e_dev_warn (char*,int) ; 
 int ixgbe_disable_sriov (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_sriov_reinit (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_vf_configuration (struct pci_dev*,int) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int pci_num_vf (struct pci_dev*) ; 

__attribute__((used)) static int ixgbe_pci_sriov_enable(struct pci_dev *dev, int num_vfs)
{
#ifdef CONFIG_PCI_IOV
	struct ixgbe_adapter *adapter = pci_get_drvdata(dev);
	int err = 0;
	int i;
	int pre_existing_vfs = pci_num_vf(dev);

	if (pre_existing_vfs && pre_existing_vfs != num_vfs)
		err = ixgbe_disable_sriov(adapter);
	else if (pre_existing_vfs && pre_existing_vfs == num_vfs)
		goto out;

	if (err)
		goto err_out;

	/* While the SR-IOV capability structure reports total VFs to be
	 * 64 we limit the actual number that can be allocated to 63 so
	 * that some transmit/receive resources can be reserved to the
	 * PF.  The PCI bus driver already checks for other values out of
	 * range.
	 */
	if (num_vfs > 63) {
		err = -EPERM;
		goto err_out;
	}

	adapter->num_vfs = num_vfs;

	err = __ixgbe_enable_sriov(adapter);
	if (err)
		goto err_out;

	for (i = 0; i < adapter->num_vfs; i++)
		ixgbe_vf_configuration(dev, (i | 0x10000000));

	err = pci_enable_sriov(dev, num_vfs);
	if (err) {
		e_dev_warn("Failed to enable PCI sriov: %d\n", err);
		goto err_out;
	}
	ixgbe_sriov_reinit(adapter);

out:
	return num_vfs;

err_out:
	return err;
#endif
	return 0;
}