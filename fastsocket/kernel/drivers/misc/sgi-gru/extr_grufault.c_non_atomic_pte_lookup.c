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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int EFAULT ; 
 int HPAGE_SHIFT ; 
 int PAGE_SHIFT ; 
 TYPE_1__* current ; 
 scalar_t__ get_user_pages (TYPE_1__*,int /*<<< orphan*/ ,unsigned long,int,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 unsigned long page_to_phys (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int non_atomic_pte_lookup(struct vm_area_struct *vma,
				 unsigned long vaddr, int write,
				 unsigned long *paddr, int *pageshift)
{
	struct page *page;

#ifdef CONFIG_HUGETLB_PAGE
	*pageshift = is_vm_hugetlb_page(vma) ? HPAGE_SHIFT : PAGE_SHIFT;
#else
	*pageshift = PAGE_SHIFT;
#endif
	if (get_user_pages
	    (current, current->mm, vaddr, 1, write, 0, &page, NULL) <= 0)
		return -EFAULT;
	*paddr = page_to_phys(page);
	put_page(page);
	return 0;
}