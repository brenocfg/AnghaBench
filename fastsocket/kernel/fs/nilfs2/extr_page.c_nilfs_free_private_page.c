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
struct page {int mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NILFS_PAGE_BUG (struct page*,char*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  try_to_free_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void nilfs_free_private_page(struct page *page)
{
	BUG_ON(!PageLocked(page));
	BUG_ON(page->mapping);

	if (page_has_buffers(page) && !try_to_free_buffers(page))
		NILFS_PAGE_BUG(page, "failed to free page");

	unlock_page(page);
	__free_page(page);
}