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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_pgoff; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int EAGAIN ; 
 int VM_IO ; 
 int VM_LOCKED ; 
 unsigned long _PAGE_CACHE ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long pgprot_val (int /*<<< orphan*/ ) ; 

int pci_mmap_page_range(struct pci_dev *dev, struct vm_area_struct *vma,
			enum pci_mmap_state mmap_state, int write_combine)
{
	unsigned long prot;

	/* Leave vm_pgoff as-is, the PCI space address is the physical
	 * address on this platform.
	 */
	vma->vm_flags |= VM_LOCKED | VM_IO;

	prot = pgprot_val(vma->vm_page_prot);
	prot &= ~_PAGE_CACHE;
	vma->vm_page_prot = __pgprot(prot);

	/* Write-combine setting is ignored */
	if (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}