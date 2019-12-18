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
struct TYPE_2__ {int /*<<< orphan*/  refused_alloc; int /*<<< orphan*/  sleep_alloc_fail; int /*<<< orphan*/  alloc_fail; int /*<<< orphan*/  sleep_alloc; int /*<<< orphan*/  alloc; } ;
struct vmballoon {scalar_t__ n_refused_pages; int /*<<< orphan*/  size; int /*<<< orphan*/  pages; int /*<<< orphan*/  refused_pages; scalar_t__ reset_required; TYPE_1__ stats; } ;
struct page {int /*<<< orphan*/  lru; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ VMW_BALLOON_MAX_REFUSED ; 
 int /*<<< orphan*/  VMW_PAGE_ALLOC_CANSLEEP ; 
 int /*<<< orphan*/  VMW_PAGE_ALLOC_NOSLEEP ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int vmballoon_send_lock_page (struct vmballoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmballoon_reserve_page(struct vmballoon *b, bool can_sleep)
{
	struct page *page;
	gfp_t flags;
	bool locked = false;

	do {
		if (!can_sleep)
			STATS_INC(b->stats.alloc);
		else
			STATS_INC(b->stats.sleep_alloc);

		flags = can_sleep ? VMW_PAGE_ALLOC_CANSLEEP : VMW_PAGE_ALLOC_NOSLEEP;
		page = alloc_page(flags);
		if (!page) {
			if (!can_sleep)
				STATS_INC(b->stats.alloc_fail);
			else
				STATS_INC(b->stats.sleep_alloc_fail);
			return -ENOMEM;
		}

		/* inform monitor */
		locked = vmballoon_send_lock_page(b, page_to_pfn(page));
		if (!locked) {
			STATS_INC(b->stats.refused_alloc);

			if (b->reset_required) {
				__free_page(page);
				return -EIO;
			}

			/*
			 * Place page on the list of non-balloonable pages
			 * and retry allocation, unless we already accumulated
			 * too many of them, in which case take a breather.
			 */
			list_add(&page->lru, &b->refused_pages);
			if (++b->n_refused_pages >= VMW_BALLOON_MAX_REFUSED)
				return -EIO;
		}
	} while (!locked);

	/* track allocated page */
	list_add(&page->lru, &b->pages);

	/* update balloon size */
	b->size++;

	return 0;
}