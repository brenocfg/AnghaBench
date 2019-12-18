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
struct pci_controller {struct celleb_pci_private* private_data; } ;
struct celleb_pci_resource {int dummy; } ;
struct celleb_pci_private {struct celleb_pci_resource*** res; } ;

/* Variables and functions */

__attribute__((used)) static struct celleb_pci_resource *get_resource_start(
				struct pci_controller *hose,
				int devno, int fn)
{
	struct celleb_pci_private *private = hose->private_data;

	if (private == NULL)
		return NULL;

	return private->res[devno][fn];
}