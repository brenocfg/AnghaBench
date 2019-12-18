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
struct resource {int /*<<< orphan*/  start; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct resource* find_oprom (struct pci_dev*) ; 
 void* ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

void *pci_map_biosrom(struct pci_dev *pdev)
{
	struct resource *oprom = find_oprom(pdev);

	if (!oprom)
		return NULL;

	return ioremap(oprom->start, resource_size(oprom));
}