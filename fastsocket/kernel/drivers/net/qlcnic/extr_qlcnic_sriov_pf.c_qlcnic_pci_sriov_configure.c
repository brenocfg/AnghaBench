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
struct qlcnic_adapter {int /*<<< orphan*/  state; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int qlcnic_pci_sriov_disable (struct qlcnic_adapter*) ; 
 int qlcnic_pci_sriov_enable (struct qlcnic_adapter*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_pci_sriov_configure(struct pci_dev *dev, int num_vfs)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(dev);
	int err;

	if (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EBUSY;

	if (num_vfs == 0)
		err = qlcnic_pci_sriov_disable(adapter);
	else
		err = qlcnic_pci_sriov_enable(adapter, num_vfs);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return err;
}