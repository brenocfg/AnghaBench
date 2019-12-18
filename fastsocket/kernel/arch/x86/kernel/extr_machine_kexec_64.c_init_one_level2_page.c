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
struct page {int dummy; } ;
struct kimage {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long PMD_MASK ; 
 int _KERNPG_TABLE ; 
 unsigned long __PAGE_KERNEL_LARGE_EXEC ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pgd (int) ; 
 int /*<<< orphan*/  __pmd (unsigned long) ; 
 int /*<<< orphan*/  __pud (int) ; 
 struct page* kimage_alloc_control_pages (struct kimage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  pgd_index (unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pud (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_one_level2_page(struct kimage *image, pgd_t *pgd,
				unsigned long addr)
{
	pud_t *pud;
	pmd_t *pmd;
	struct page *page;
	int result = -ENOMEM;

	addr &= PMD_MASK;
	pgd += pgd_index(addr);
	if (!pgd_present(*pgd)) {
		page = kimage_alloc_control_pages(image, 0);
		if (!page)
			goto out;
		pud = (pud_t *)page_address(page);
		memset(pud, 0, PAGE_SIZE);
		set_pgd(pgd, __pgd(__pa(pud) | _KERNPG_TABLE));
	}
	pud = pud_offset(pgd, addr);
	if (!pud_present(*pud)) {
		page = kimage_alloc_control_pages(image, 0);
		if (!page)
			goto out;
		pmd = (pmd_t *)page_address(page);
		memset(pmd, 0, PAGE_SIZE);
		set_pud(pud, __pud(__pa(pmd) | _KERNPG_TABLE));
	}
	pmd = pmd_offset(pud, addr);
	if (!pmd_present(*pmd))
		set_pmd(pmd, __pmd(addr | __PAGE_KERNEL_LARGE_EXEC));
	result = 0;
out:
	return result;
}