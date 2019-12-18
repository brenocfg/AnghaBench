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
struct efx_nic {struct pci_dev* pci_dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ eeh_dn_check_failure (struct device_node*,struct pci_dev*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 

int efx_try_recovery(struct efx_nic *efx)
{
#ifdef CONFIG_EEH
	/* A PCI error can occur and not be seen by EEH because nothing
	 * happens on the PCI bus. In this case the driver may fail and
	 * schedule a 'recover or reset', leading to this recovery handler.
	 * Manually call the eeh failure check function.
	 */
	struct pci_dev *pcidev = efx->pci_dev;
	struct device_node *dn = pci_device_to_OF_node(pcidev);

	if (eeh_dn_check_failure(dn, pcidev)) {
		/* The EEH mechanisms will handle the error and reset the
		 * device if necessary.
		 */
		return 1;
	}
#endif
	return 0;
}