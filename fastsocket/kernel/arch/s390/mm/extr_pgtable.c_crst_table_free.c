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
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_lock; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ORDER ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long* get_shadow_table (unsigned long*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (unsigned long*) ; 

void crst_table_free(struct mm_struct *mm, unsigned long *table)
{
	unsigned long *shadow = get_shadow_table(table);
	struct page *page = virt_to_page(table);

	spin_lock(&mm->context.list_lock);
	list_del(&page->lru);
	spin_unlock(&mm->context.list_lock);
	if (shadow)
		free_pages((unsigned long) shadow, ALLOC_ORDER);
	free_pages((unsigned long) table, ALLOC_ORDER);
}