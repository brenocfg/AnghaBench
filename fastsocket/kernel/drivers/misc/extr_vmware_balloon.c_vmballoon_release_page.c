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
struct TYPE_2__ {int /*<<< orphan*/  free; } ;
struct vmballoon {int /*<<< orphan*/  size; TYPE_1__ stats; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  vmballoon_send_unlock_page (struct vmballoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmballoon_release_page(struct vmballoon *b, struct page *page)
{
	if (!vmballoon_send_unlock_page(b, page_to_pfn(page)))
		return -EIO;

	list_del(&page->lru);

	/* deallocate page */
	__free_page(page);
	STATS_INC(b->stats.free);

	/* update balloon size */
	b->size--;

	return 0;
}