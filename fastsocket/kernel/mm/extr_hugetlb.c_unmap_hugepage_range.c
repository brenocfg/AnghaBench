#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_2__* vm_file; int /*<<< orphan*/  vm_flags; } ;
struct page {int dummy; } ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mmap_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAYSHARE ; 
 int /*<<< orphan*/  __unmap_hugepage_range (struct vm_area_struct*,unsigned long,unsigned long,struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void unmap_hugepage_range(struct vm_area_struct *vma, unsigned long start,
			  unsigned long end, struct page *ref_page)
{
	spin_lock(&vma->vm_file->f_mapping->i_mmap_lock);
	__unmap_hugepage_range(vma, start, end, ref_page);
	/*
	 * Clear this flag so that x86's huge_pmd_share page_table_shareable
	 * test will fail on a vma being torn down, and not grab a page table
	 * on its way out.  We're lucky that the flag has such an appropriate
	 * name, and can in fact be safely cleared here. We could clear it
	 * before the __unmap_hugepage_range above, but all that's necessary
	 * is to clear it before releasing the i_mmap_lock. This works
	 * because in the context this is called, the VMA is about to be
	 * destroyed and the i_mmap_lock is held.
	 */
	vma->vm_flags &= ~VM_MAYSHARE;
	spin_unlock(&vma->vm_file->f_mapping->i_mmap_lock);
}