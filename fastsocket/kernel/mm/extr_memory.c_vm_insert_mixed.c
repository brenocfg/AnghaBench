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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EFAULT ; 
 int /*<<< orphan*/  HAVE_PTE_SPECIAL ; 
 int VM_MIXEDMAP ; 
 int insert_page (struct vm_area_struct*,unsigned long,struct page*,int /*<<< orphan*/ ) ; 
 int insert_pfn (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 

int vm_insert_mixed(struct vm_area_struct *vma, unsigned long addr,
			unsigned long pfn)
{
	BUG_ON(!(vma->vm_flags & VM_MIXEDMAP));

	if (addr < vma->vm_start || addr >= vma->vm_end)
		return -EFAULT;

	/*
	 * If we don't have pte special, then we have to use the pfn_valid()
	 * based VM_MIXEDMAP scheme (see vm_normal_page), and thus we *must*
	 * refcount the page if pfn_valid is true (hence insert_page rather
	 * than insert_pfn).  If a zero_pfn were inserted into a VM_MIXEDMAP
	 * without pte special, it would there be refcounted as a normal page.
	 */
	if (!HAVE_PTE_SPECIAL && pfn_valid(pfn)) {
		struct page *page;

		page = pfn_to_page(pfn);
		return insert_page(vma, addr, page, vma->vm_page_prot);
	}
	return insert_pfn(vma, addr, pfn, vma->vm_page_prot);
}