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
struct vm_area_struct {unsigned int vm_end; unsigned int vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct ipath_portdata {int dummy; } ;
struct ipath_devdata {unsigned int ipath_palign; unsigned int ipath_physaddr; TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int VM_DONTCOPY ; 
 int VM_DONTEXPAND ; 
 int VM_MAYREAD ; 
 int /*<<< orphan*/  _PAGE_GUARDED ; 
 int /*<<< orphan*/  _PAGE_NO_CACHE ; 
 int /*<<< orphan*/  _PAGE_WRITETHRU ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int io_remap_pfn_range (struct vm_area_struct*,unsigned int,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmap_piobufs(struct vm_area_struct *vma,
			struct ipath_devdata *dd,
			struct ipath_portdata *pd,
			unsigned piobufs, unsigned piocnt)
{
	unsigned long phys;
	int ret;

	/*
	 * When we map the PIO buffers in the chip, we want to map them as
	 * writeonly, no read possible.   This prevents access to previous
	 * process data, and catches users who might try to read the i/o
	 * space due to a bug.
	 */
	if ((vma->vm_end - vma->vm_start) > (piocnt * dd->ipath_palign)) {
		dev_info(&dd->pcidev->dev, "FAIL mmap piobufs: "
			 "reqlen %lx > PAGE\n",
			 vma->vm_end - vma->vm_start);
		ret = -EINVAL;
		goto bail;
	}

	phys = dd->ipath_physaddr + piobufs;

#if defined(__powerpc__)
	/* There isn't a generic way to specify writethrough mappings */
	pgprot_val(vma->vm_page_prot) |= _PAGE_NO_CACHE;
	pgprot_val(vma->vm_page_prot) |= _PAGE_WRITETHRU;
	pgprot_val(vma->vm_page_prot) &= ~_PAGE_GUARDED;
#endif

	/*
	 * don't allow them to later change to readable with mprotect (for when
	 * not initially mapped readable, as is normally the case)
	 */
	vma->vm_flags &= ~VM_MAYREAD;
	vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND;

	ret = io_remap_pfn_range(vma, vma->vm_start, phys >> PAGE_SHIFT,
				 vma->vm_end - vma->vm_start,
				 vma->vm_page_prot);
bail:
	return ret;
}