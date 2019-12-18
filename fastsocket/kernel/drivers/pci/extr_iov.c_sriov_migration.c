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
typedef  int u16 ;
struct pci_sriov {int cap; int /*<<< orphan*/  mtask; scalar_t__ pos; int /*<<< orphan*/  nr_virtfn; } ;
struct pci_dev {struct pci_sriov* sriov; } ;

/* Variables and functions */
 int PCI_SRIOV_CAP_VFM ; 
 scalar_t__ PCI_SRIOV_STATUS ; 
 int PCI_SRIOV_STATUS_VFM ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sriov_migration(struct pci_dev *dev)
{
	u16 status;
	struct pci_sriov *iov = dev->sriov;

	if (!iov->nr_virtfn)
		return 0;

	if (!(iov->cap & PCI_SRIOV_CAP_VFM))
		return 0;

	pci_read_config_word(dev, iov->pos + PCI_SRIOV_STATUS, &status);
	if (!(status & PCI_SRIOV_STATUS_VFM))
		return 0;

	schedule_work(&iov->mtask);

	return 1;
}