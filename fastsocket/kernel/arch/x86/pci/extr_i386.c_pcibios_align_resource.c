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
struct resource {int flags; int start; } ;
struct pci_dev {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 scalar_t__ skip_isa_ioresource_align (struct pci_dev*) ; 

void
pcibios_align_resource(void *data, struct resource *res,
			resource_size_t size, resource_size_t align)
{
	struct pci_dev *dev = data;

	if (res->flags & IORESOURCE_IO) {
		resource_size_t start = res->start;

		if (skip_isa_ioresource_align(dev))
			return;
		if (start & 0x300) {
			start = (start + 0x3ff) & ~0x3ff;
			res->start = start;
		}
	}
}