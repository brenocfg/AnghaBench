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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_MASK ; 
 unsigned long PGDIR_SIZE ; 
 unsigned long PTRS_PER_PGD ; 
 int _KERNPG_TABLE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pgd (int) ; 
 int init_level3_page (struct kimage*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 struct page* kimage_alloc_control_pages (struct kimage*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_level4_page(struct kimage *image, pgd_t *level4p,
				unsigned long addr, unsigned long last_addr)
{
	unsigned long end_addr;
	int result;

	result = 0;
	addr &= PAGE_MASK;
	end_addr = addr + (PTRS_PER_PGD * PGDIR_SIZE);
	while ((addr < last_addr) && (addr < end_addr)) {
		struct page *page;
		pud_t *level3p;

		page = kimage_alloc_control_pages(image, 0);
		if (!page) {
			result = -ENOMEM;
			goto out;
		}
		level3p = (pud_t *)page_address(page);
		result = init_level3_page(image, level3p, addr, last_addr);
		if (result)
			goto out;
		set_pgd(level4p++, __pgd(__pa(level3p) | _KERNPG_TABLE));
		addr += PGDIR_SIZE;
	}
	/* clear the unused entries */
	while (addr < end_addr) {
		pgd_clear(level4p++);
		addr += PGDIR_SIZE;
	}
out:
	return result;
}