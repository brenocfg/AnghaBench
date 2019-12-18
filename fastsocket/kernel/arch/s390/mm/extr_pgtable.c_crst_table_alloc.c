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
struct page {int /*<<< orphan*/  lru; scalar_t__ index; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  crst_list; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ORDER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned long *crst_table_alloc(struct mm_struct *mm, int noexec)
{
	struct page *page = alloc_pages(GFP_KERNEL, ALLOC_ORDER);

	if (!page)
		return NULL;
	page->index = 0;
	if (noexec) {
		struct page *shadow = alloc_pages(GFP_KERNEL, ALLOC_ORDER);
		if (!shadow) {
			__free_pages(page, ALLOC_ORDER);
			return NULL;
		}
		page->index = page_to_phys(shadow);
	}
	spin_lock(&mm->context.list_lock);
	list_add(&page->lru, &mm->context.crst_list);
	spin_unlock(&mm->context.list_lock);
	return (unsigned long *) page_to_phys(page);
}