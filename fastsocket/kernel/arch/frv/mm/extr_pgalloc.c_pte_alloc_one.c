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
struct mm_struct {int dummy; } ;
typedef  struct page* pgtable_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_HIGHMEM ; 
 int __GFP_REPEAT ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_highpage (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  pgtable_page_ctor (struct page*) ; 

pgtable_t pte_alloc_one(struct mm_struct *mm, unsigned long address)
{
	struct page *page;

#ifdef CONFIG_HIGHPTE
	page = alloc_pages(GFP_KERNEL|__GFP_HIGHMEM|__GFP_REPEAT, 0);
#else
	page = alloc_pages(GFP_KERNEL|__GFP_REPEAT, 0);
#endif
	if (page) {
		clear_highpage(page);
		pgtable_page_ctor(page);
		flush_dcache_page(page);
	}
	return page;
}