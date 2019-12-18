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

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ map_tboot_page (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tboot_mm ; 
 int /*<<< orphan*/  tboot_pg_dir ; 

__attribute__((used)) static int map_tboot_pages(unsigned long vaddr, unsigned long start_pfn,
			   unsigned long nr)
{
	/* Reuse the original kernel mapping */
	tboot_pg_dir = pgd_alloc(&tboot_mm);
	if (!tboot_pg_dir)
		return -1;

	for (; nr > 0; nr--, vaddr += PAGE_SIZE, start_pfn++) {
		if (map_tboot_page(vaddr, start_pfn, PAGE_KERNEL_EXEC))
			return -1;
	}

	return 0;
}