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
struct vm_area_struct {int vm_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_SIZE ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_LOCKED ; 
 int VM_PFNMAP ; 
 int VM_RESERVED ; 
 int /*<<< orphan*/  __mlock_vma_pages_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 TYPE_1__* current ; 
 struct vm_area_struct* get_gate_vma (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  make_pages_present (unsigned long,unsigned long) ; 

long mlock_vma_pages_range(struct vm_area_struct *vma,
			unsigned long start, unsigned long end)
{
	int nr_pages = (end - start) / PAGE_SIZE;
	BUG_ON(!(vma->vm_flags & VM_LOCKED));

	/*
	 * filter unlockable vmas
	 */
	if (vma->vm_flags & (VM_IO | VM_PFNMAP))
		goto no_mlock;

	if (!((vma->vm_flags & (VM_DONTEXPAND | VM_RESERVED)) ||
			is_vm_hugetlb_page(vma) ||
			vma == get_gate_vma(current->mm))) {

		__mlock_vma_pages_range(vma, start, end);

		/* Hide errors from mmap() and other callers */
		return 0;
	}

	/*
	 * User mapped kernel pages or huge pages:
	 * make these pages present to populate the ptes, but
	 * fall thru' to reset VM_LOCKED--no need to unlock, and
	 * return nr_pages so these don't get counted against task's
	 * locked limit.  huge pages are already counted against
	 * locked vm limit.
	 */
	make_pages_present(start, end);

no_mlock:
	vma->vm_flags &= ~VM_LOCKED;	/* and don't come back! */
	return nr_pages;		/* error or pages NOT mlocked */
}