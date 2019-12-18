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
struct MPT2SAS_ADAPTER {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_remove_bus_device (struct pci_dev*) ; 

__attribute__((used)) static int mpt2sas_remove_dead_ioc_func(void *arg)
{
		struct MPT2SAS_ADAPTER *ioc = (struct MPT2SAS_ADAPTER *)arg;
		struct pci_dev *pdev;

		if ((ioc == NULL))
			return -1;

		pdev = ioc->pdev;
		if ((pdev == NULL))
			return -1;
		pci_remove_bus_device(pdev);
		return 0;
}