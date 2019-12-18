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

/* Variables and functions */
 int PCI_CAP_ID_MSIX ; 
 int check_req_msi (struct pci_dev*,int) ; 
 int check_req_msix (struct pci_dev*,int) ; 
 int msi_quota_for_device (struct pci_dev*,int) ; 

__attribute__((used)) static int rtas_msi_check_device(struct pci_dev *pdev, int nvec, int type)
{
	int quota, rc;

	if (type == PCI_CAP_ID_MSIX)
		rc = check_req_msix(pdev, nvec);
	else
		rc = check_req_msi(pdev, nvec);

	if (rc)
		return rc;

	quota = msi_quota_for_device(pdev, nvec);

	if (quota && quota < nvec)
		return quota;

	return 0;
}