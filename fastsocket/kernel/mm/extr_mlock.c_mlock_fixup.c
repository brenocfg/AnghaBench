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
struct vm_area_struct {unsigned int vm_flags; unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  anon_vma; scalar_t__ vm_pgoff; struct mm_struct* vm_mm; } ;
struct mm_struct {int locked_vm; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 unsigned int VM_LOCKED ; 
 int VM_PFNMAP ; 
 int VM_RESERVED ; 
 int __mlock_posix_error_return (int) ; 
 int __mlock_vma_pages_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 TYPE_1__* current ; 
 struct vm_area_struct* get_gate_vma (int /*<<< orphan*/ ) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  make_pages_present (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  munlock_vma_pages_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int split_vma (struct mm_struct*,struct vm_area_struct*,unsigned long,int) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

__attribute__((used)) static int mlock_fixup(struct vm_area_struct *vma, struct vm_area_struct **prev,
	unsigned long start, unsigned long end, unsigned int newflags)
{
	struct mm_struct *mm = vma->vm_mm;
	pgoff_t pgoff;
	int nr_pages;
	int ret = 0;
	int lock = newflags & VM_LOCKED;

	if (newflags == vma->vm_flags ||
			(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		goto out;	/* don't set VM_LOCKED,  don't count */

	if ((vma->vm_flags & (VM_DONTEXPAND | VM_RESERVED)) ||
			is_vm_hugetlb_page(vma) ||
			vma == get_gate_vma(current->mm)) {
		if (lock)
			make_pages_present(start, end);
		goto out;	/* don't set VM_LOCKED,  don't count */
	}

	pgoff = vma->vm_pgoff + ((start - vma->vm_start) >> PAGE_SHIFT);
	*prev = vma_merge(mm, *prev, start, end, newflags, vma->anon_vma,
			  vma->vm_file, pgoff, vma_policy(vma));
	if (*prev) {
		vma = *prev;
		goto success;
	}

	if (start != vma->vm_start) {
		ret = split_vma(mm, vma, start, 1);
		if (ret)
			goto out;
	}

	if (end != vma->vm_end) {
		ret = split_vma(mm, vma, end, 0);
		if (ret)
			goto out;
	}

success:
	/*
	 * Keep track of amount of locked VM.
	 */
	nr_pages = (end - start) >> PAGE_SHIFT;
	if (!lock)
		nr_pages = -nr_pages;
	mm->locked_vm += nr_pages;

	/*
	 * vm_flags is protected by the mmap_sem held in write mode.
	 * It's okay if try_to_unmap_one unmaps a page just after we
	 * set VM_LOCKED, __mlock_vma_pages_range will bring it back.
	 */

	if (lock) {
		vma->vm_flags = newflags;
		ret = __mlock_vma_pages_range(vma, start, end);
		if (ret < 0)
			ret = __mlock_posix_error_return(ret);
	} else {
		munlock_vma_pages_range(vma, start, end);
	}

out:
	*prev = vma;
	return ret;
}