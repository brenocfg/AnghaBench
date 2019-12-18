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
struct vm_area_struct {unsigned long vm_pgoff; int vm_flags; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct pci_controller {unsigned long sparse_mem_base; unsigned long dense_mem_base; unsigned long sparse_io_base; unsigned long dense_io_base; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int VM_IO ; 
 int VM_RESERVED ; 
 int io_remap_pfn_range (struct vm_area_struct*,scalar_t__,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 int pci_mmap_mem ; 

__attribute__((used)) static int hose_mmap_page_range(struct pci_controller *hose,
				struct vm_area_struct *vma,
				enum pci_mmap_state mmap_type, int sparse)
{
	unsigned long base;

	if (mmap_type == pci_mmap_mem)
		base = sparse ? hose->sparse_mem_base : hose->dense_mem_base;
	else
		base = sparse ? hose->sparse_io_base : hose->dense_io_base;

	vma->vm_pgoff += base >> PAGE_SHIFT;
	vma->vm_flags |= (VM_IO | VM_RESERVED);

	return io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				  vma->vm_end - vma->vm_start,
				  vma->vm_page_prot);
}