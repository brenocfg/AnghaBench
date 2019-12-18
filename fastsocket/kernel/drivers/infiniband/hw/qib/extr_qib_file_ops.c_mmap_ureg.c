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
typedef  unsigned long u64 ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct qib_devdata {int flags; unsigned long physaddr; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int QIB_HAS_HDRSUPP ; 
 int VM_DONTCOPY ; 
 int VM_DONTEXPAND ; 
 int io_remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int mmap_ureg(struct vm_area_struct *vma, struct qib_devdata *dd,
		     u64 ureg)
{
	unsigned long phys;
	unsigned long sz;
	int ret;

	/*
	 * This is real hardware, so use io_remap.  This is the mechanism
	 * for the user process to update the head registers for their ctxt
	 * in the chip.
	 */
	sz = dd->flags & QIB_HAS_HDRSUPP ? 2 * PAGE_SIZE : PAGE_SIZE;
	if ((vma->vm_end - vma->vm_start) > sz) {
		qib_devinfo(dd->pcidev,
			"FAIL mmap userreg: reqlen %lx > PAGE\n",
			vma->vm_end - vma->vm_start);
		ret = -EFAULT;
	} else {
		phys = dd->physaddr + ureg;
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

		vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND;
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 phys >> PAGE_SHIFT,
					 vma->vm_end - vma->vm_start,
					 vma->vm_page_prot);
	}
	return ret;
}