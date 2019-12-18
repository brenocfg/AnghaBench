#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_pgoff; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 unsigned long _PAGE_CACHE_UC_MINUS ; 
 unsigned long _PAGE_CACHE_WC ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 TYPE_1__ boot_cpu_data ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pat_enabled ; 
 int pci_mmap_io ; 
 int /*<<< orphan*/  pci_mmap_ops ; 
 unsigned long pgprot_val (int /*<<< orphan*/ ) ; 

int pci_mmap_page_range(struct pci_dev *dev, struct vm_area_struct *vma,
			enum pci_mmap_state mmap_state, int write_combine)
{
	unsigned long prot;

	/* I/O space cannot be accessed via normal processor loads and
	 * stores on this platform.
	 */
	if (mmap_state == pci_mmap_io)
		return -EINVAL;

	prot = pgprot_val(vma->vm_page_prot);

	/*
 	 * Return error if pat is not enabled and write_combine is requested.
 	 * Caller can followup with UC MINUS request and add a WC mtrr if there
 	 * is a free mtrr slot.
 	 */
	if (!pat_enabled && write_combine)
		return -EINVAL;

	if (pat_enabled && write_combine)
		prot |= _PAGE_CACHE_WC;
	else if (pat_enabled || boot_cpu_data.x86 > 3)
		/*
		 * ioremap() and ioremap_nocache() defaults to UC MINUS for now.
		 * To avoid attribute conflicts, request UC MINUS here
		 * aswell.
		 */
		prot |= _PAGE_CACHE_UC_MINUS;

	vma->vm_page_prot = __pgprot(prot);

	if (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot))
		return -EAGAIN;

	vma->vm_ops = &pci_mmap_ops;

	return 0;
}