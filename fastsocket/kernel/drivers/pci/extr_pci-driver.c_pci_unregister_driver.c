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
struct pci_driver {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_dynids (struct pci_driver*) ; 
 int /*<<< orphan*/  pci_remove_newid_file (struct pci_driver*) ; 
 int /*<<< orphan*/  pci_remove_removeid_file (struct pci_driver*) ; 

void
pci_unregister_driver(struct pci_driver *drv)
{
	pci_remove_removeid_file(drv);
	pci_remove_newid_file(drv);
	driver_unregister(&drv->driver);
	pci_free_dynids(drv);
}