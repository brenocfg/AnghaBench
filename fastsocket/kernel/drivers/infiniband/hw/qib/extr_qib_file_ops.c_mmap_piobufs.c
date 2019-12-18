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
struct vm_area_struct {unsigned int vm_end; unsigned int vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct qib_devdata {unsigned int palign; unsigned int physaddr; int /*<<< orphan*/  pcidev; } ;
struct qib_ctxtdata {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int VM_DONTCOPY ; 
 int VM_DONTEXPAND ; 
 int VM_MAYREAD ; 
 int /*<<< orphan*/  _PAGE_GUARDED ; 
 int /*<<< orphan*/  _PAGE_NO_CACHE ; 
 int /*<<< orphan*/  _PAGE_WRITETHRU ; 
 int io_remap_pfn_range (struct vm_area_struct*,unsigned int,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ qib_wc_pat ; 

__attribute__((used)) static int mmap_piobufs(struct vm_area_struct *vma,
			struct qib_devdata *dd,
			struct qib_ctxtdata *rcd,
			unsigned piobufs, unsigned piocnt)
{
	unsigned long phys;
	int ret;

	/*
	 * When we map the PIO buffers in the chip, we want to map them as
	 * writeonly, no read possible; unfortunately, x86 doesn't allow
	 * for this in hardware, but we still prevent users from asking
	 * for it.
	 */
	if ((vma->vm_end - vma->vm_start) > (piocnt * dd->palign)) {
		qib_devinfo(dd->pcidev,
			"FAIL mmap piobufs: reqlen %lx > PAGE\n",
			 vma->vm_end - vma->vm_start);
		ret = -EINVAL;
		goto bail;
	}

	phys = dd->physaddr + piobufs;

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

	if (qib_wc_pat)
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	ret = io_remap_pfn_range(vma, vma->vm_start, phys >> PAGE_SHIFT,
				 vma->vm_end - vma->vm_start,
				 vma->vm_page_prot);
bail:
	return ret;
}