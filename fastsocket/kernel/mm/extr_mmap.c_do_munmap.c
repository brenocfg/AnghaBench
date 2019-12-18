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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_flags; struct vm_area_struct* vm_next; } ;
struct mm_struct {scalar_t__ map_count; scalar_t__ locked_vm; struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_MASK ; 
 unsigned long TASK_SIZE ; 
 int VM_LOCKED ; 
 int __split_vma (struct mm_struct*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  detach_vmas_to_be_unmapped (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma_prev (struct mm_struct*,unsigned long,struct vm_area_struct**) ; 
 int /*<<< orphan*/  munlock_vma_pages_all (struct vm_area_struct*) ; 
 int /*<<< orphan*/  remove_vma_list (struct mm_struct*,struct vm_area_struct*) ; 
 scalar_t__ sysctl_max_map_count ; 
 int /*<<< orphan*/  unmap_region (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,unsigned long,unsigned long) ; 
 scalar_t__ vma_pages (struct vm_area_struct*) ; 

int do_munmap(struct mm_struct *mm, unsigned long start, size_t len)
{
	unsigned long end;
	struct vm_area_struct *vma, *prev, *last;

	if ((start & ~PAGE_MASK) || start > TASK_SIZE || len > TASK_SIZE-start)
		return -EINVAL;

	if ((len = PAGE_ALIGN(len)) == 0)
		return -EINVAL;

	/* Find the first overlapping VMA */
	vma = find_vma_prev(mm, start, &prev);
	if (!vma)
		return 0;
	/* we have  start < vma->vm_end  */

	/* if it doesn't overlap, we have nothing.. */
	end = start + len;
	if (vma->vm_start >= end)
		return 0;

	/*
	 * If we need to split any vma, do it now to save pain later.
	 *
	 * Note: mremap's move_vma VM_ACCOUNT handling assumes a partially
	 * unmapped vm_area_struct will remain in use: so lower split_vma
	 * places tmp vma above, and higher split_vma places tmp vma below.
	 */
	if (start > vma->vm_start) {
		int error;

		/*
		 * Make sure that map_count on return from munmap() will
		 * not exceed its limit; but let map_count go just above
		 * its limit temporarily, to help free resources as expected.
		 */
		if (end < vma->vm_end && mm->map_count >= sysctl_max_map_count)
			return -ENOMEM;

		error = __split_vma(mm, vma, start, 0);
		if (error)
			return error;
		prev = vma;
	}

	/* Does it split the last one? */
	last = find_vma(mm, end);
	if (last && end > last->vm_start) {
		int error = __split_vma(mm, last, end, 1);
		if (error)
			return error;
	}
	vma = prev? prev->vm_next: mm->mmap;

	/*
	 * unlock any mlock()ed ranges before detaching vmas
	 */
	if (mm->locked_vm) {
		struct vm_area_struct *tmp = vma;
		while (tmp && tmp->vm_start < end) {
			if (tmp->vm_flags & VM_LOCKED) {
				mm->locked_vm -= vma_pages(tmp);
				munlock_vma_pages_all(tmp);
			}
			tmp = tmp->vm_next;
		}
	}

	/*
	 * Remove the vma's, and unmap the actual pages
	 */
	detach_vmas_to_be_unmapped(mm, vma, prev, end);
	unmap_region(mm, vma, prev, start, end);

	/* Fix up all other VM information */
	remove_vma_list(mm, vma);

	return 0;
}