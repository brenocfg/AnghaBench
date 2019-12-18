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
struct resource {int flags; scalar_t__ end; scalar_t__ start; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {scalar_t__ pci_mem_offset; scalar_t__ io_base_virt; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 scalar_t__ _IO_BASE ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 

void pci_resource_to_user(const struct pci_dev *dev, int bar,
			  const struct resource *rsrc,
			  resource_size_t *start, resource_size_t *end)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	resource_size_t offset = 0;

	if (hose == NULL)
		return;

	if (rsrc->flags & IORESOURCE_IO)
		offset = (unsigned long)hose->io_base_virt - _IO_BASE;

	/* We pass a fully fixed up address to userland for MMIO instead of
	 * a BAR value because X is lame and expects to be able to use that
	 * to pass to /dev/mem !
	 *
	 * That means that we'll have potentially 64 bits values where some
	 * userland apps only expect 32 (like X itself since it thinks only
	 * Sparc has 64 bits MMIO) but if we don't do that, we break it on
	 * 32 bits CHRPs :-(
	 *
	 * Hopefully, the sysfs insterface is immune to that gunk. Once X
	 * has been fixed (and the fix spread enough), we can re-enable the
	 * 2 lines below and pass down a BAR value to userland. In that case
	 * we'll also have to re-enable the matching code in
	 * __pci_mmap_make_offset().
	 *
	 * BenH.
	 */
#if 0
	else if (rsrc->flags & IORESOURCE_MEM)
		offset = hose->pci_mem_offset;
#endif

	*start = rsrc->start - offset;
	*end = rsrc->end - offset;
}