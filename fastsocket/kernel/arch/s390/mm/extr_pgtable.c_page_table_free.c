#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {unsigned long flags; int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  pgtable_list; scalar_t__ has_pgste; scalar_t__ noexec; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int FRAG_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int __pa (unsigned long*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (int) ; 
 int /*<<< orphan*/  pgtable_page_dtor (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void page_table_free(struct mm_struct *mm, unsigned long *table)
{
	struct page *page;
	unsigned long bits;

	bits = (mm->context.noexec || mm->context.has_pgste) ? 3UL : 1UL;
	bits <<= (__pa(table) & (PAGE_SIZE - 1)) / 256 / sizeof(unsigned long);
	page = pfn_to_page(__pa(table) >> PAGE_SHIFT);
	spin_lock(&mm->context.list_lock);
	page->flags ^= bits;
	if (page->flags & FRAG_MASK) {
		/* Page now has some free pgtable fragments. */
		list_move(&page->lru, &mm->context.pgtable_list);
		page = NULL;
	} else
		/* All fragments of the 4K page have been freed. */
		list_del(&page->lru);
	spin_unlock(&mm->context.list_lock);
	if (page) {
		pgtable_page_dtor(page);
		__free_page(page);
	}
}