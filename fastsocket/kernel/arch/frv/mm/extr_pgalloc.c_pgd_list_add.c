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
struct page {unsigned long index; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 struct page* pgd_list ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 struct page* virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pgd_list_add(pgd_t *pgd)
{
	struct page *page = virt_to_page(pgd);
	page->index = (unsigned long) pgd_list;
	if (pgd_list)
		set_page_private(pgd_list, (unsigned long) &page->index);
	pgd_list = page;
	set_page_private(page, (unsigned long)&pgd_list);
}