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
struct page {unsigned long private; } ;
struct mm_struct {int /*<<< orphan*/ * pgd; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PagePinned (struct page*) ; 
 int /*<<< orphan*/  VSYSCALL_START ; 
 int _PAGE_TABLE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_page (int) ; 
 int __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pgd (int) ; 
 int /*<<< orphan*/  level3_user_vsyscall ; 
 size_t pgd_index (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xen_get_user_pgd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xen_pgd_alloc(struct mm_struct *mm)
{
	pgd_t *pgd = mm->pgd;
	int ret = 0;

	BUG_ON(PagePinned(virt_to_page(pgd)));

#ifdef CONFIG_X86_64
	{
		struct page *page = virt_to_page(pgd);
		pgd_t *user_pgd;

		BUG_ON(page->private != 0);

		ret = -ENOMEM;

		user_pgd = (pgd_t *)__get_free_page(GFP_KERNEL | __GFP_ZERO);
		page->private = (unsigned long)user_pgd;

		if (user_pgd != NULL) {
			user_pgd[pgd_index(VSYSCALL_START)] =
				__pgd(__pa(level3_user_vsyscall) | _PAGE_TABLE);
			ret = 0;
		}

		BUG_ON(PagePinned(virt_to_page(xen_get_user_pgd(pgd))));
	}
#endif

	return ret;
}