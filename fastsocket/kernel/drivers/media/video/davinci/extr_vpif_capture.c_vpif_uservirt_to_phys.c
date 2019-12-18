#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct vm_area_struct {int vm_flags; unsigned long vm_pgoff; unsigned long vm_start; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_3__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_OFFSET ; 
 unsigned long PAGE_SHIFT ; 
 int VM_IO ; 
 unsigned long __pa (scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int get_user_pages (TYPE_1__*,struct mm_struct*,unsigned long,int,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 unsigned long virt_to_phys (void*) ; 
 int /*<<< orphan*/  vpif_err (char*) ; 

__attribute__((used)) static inline u32 vpif_uservirt_to_phys(u32 virtp)
{
	unsigned long physp = 0;
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;

	vma = find_vma(mm, virtp);

	/* For kernel direct-mapped memory, take the easy way */
	if (virtp >= PAGE_OFFSET)
		physp = virt_to_phys((void *)virtp);
	else if (vma && (vma->vm_flags & VM_IO) && (vma->vm_pgoff))
		/**
		 * this will catch, kernel-allocated, mmaped-to-usermode
		 * addresses
		 */
		physp = (vma->vm_pgoff << PAGE_SHIFT) + (virtp - vma->vm_start);
	else {
		/* otherwise, use get_user_pages() for general userland pages */
		int res, nr_pages = 1;
			struct page *pages;

		down_read(&current->mm->mmap_sem);

		res = get_user_pages(current, current->mm,
				     virtp, nr_pages, 1, 0, &pages, NULL);
		up_read(&current->mm->mmap_sem);

		if (res == nr_pages)
			physp = __pa(page_address(&pages[0]) +
				     (virtp & ~PAGE_MASK));
		else {
			vpif_err("get_user_pages failed\n");
			return 0;
		}
	}
	return physp;
}