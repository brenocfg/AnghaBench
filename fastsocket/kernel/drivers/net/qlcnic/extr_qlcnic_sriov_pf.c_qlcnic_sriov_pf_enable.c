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
struct qlcnic_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int pci_enable_sriov (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlcnic_sriov_enable_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_cleanup (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_enable(struct qlcnic_adapter *adapter, int num_vfs)
{
	int err;

	if (!qlcnic_sriov_enable_check(adapter))
		return 0;

	err = pci_enable_sriov(adapter->pdev, num_vfs);
	if (err)
		qlcnic_sriov_pf_cleanup(adapter);

	return err;
}