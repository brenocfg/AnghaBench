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
struct fnic {int /*<<< orphan*/  vdev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNIC_DEV_INTR_MODE_INTX ; 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_dev_set_intr_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fnic_clear_intr_mode(struct fnic *fnic)
{
	switch (vnic_dev_get_intr_mode(fnic->vdev)) {
	case VNIC_DEV_INTR_MODE_MSIX:
		pci_disable_msix(fnic->pdev);
		break;
	case VNIC_DEV_INTR_MODE_MSI:
		pci_disable_msi(fnic->pdev);
		break;
	default:
		break;
	}

	vnic_dev_set_intr_mode(fnic->vdev, VNIC_DEV_INTR_MODE_INTX);
}