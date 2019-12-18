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
struct zone {int dummy; } ;
struct per_cpu_pages {scalar_t__ count; scalar_t__ high; scalar_t__ batch; int /*<<< orphan*/ * lists; } ;
struct page {int /*<<< orphan*/  lru; int /*<<< orphan*/ * mapping; } ;
struct TYPE_2__ {struct per_cpu_pages pcp; } ;

/* Variables and functions */
 int MIGRATE_ISOLATE ; 
 int MIGRATE_MOVABLE ; 
 int MIGRATE_PCPTYPES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PGFREE ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int __TestClearPageMlocked (struct page*) ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_free_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_check_no_obj_freed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_one_page (struct zone*,struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_page_mlock (struct page*) ; 
 scalar_t__ free_pages_check (struct page*) ; 
 int /*<<< orphan*/  free_pcppages_bulk (struct zone*,scalar_t__,struct per_cpu_pages*) ; 
 int /*<<< orphan*/  get_cpu () ; 
 int get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  kernel_map_pages (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemcheck_free_shadow (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  set_page_private (struct page*,int) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* zone_pcp (struct zone*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_hot_cold_page(struct page *page, int cold)
{
	struct zone *zone = page_zone(page);
	struct per_cpu_pages *pcp;
	unsigned long flags;
	int migratetype;
	int wasMlocked = __TestClearPageMlocked(page);

	kmemcheck_free_shadow(page, 0);

	if (PageAnon(page))
		page->mapping = NULL;
	if (free_pages_check(page))
		return;

	if (!PageHighMem(page)) {
		debug_check_no_locks_freed(page_address(page), PAGE_SIZE);
		debug_check_no_obj_freed(page_address(page), PAGE_SIZE);
	}
	arch_free_page(page, 0);
	kernel_map_pages(page, 1, 0);

	pcp = &zone_pcp(zone, get_cpu())->pcp;
	migratetype = get_pageblock_migratetype(page);
	set_page_private(page, migratetype);
	local_irq_save(flags);
	if (unlikely(wasMlocked))
		free_page_mlock(page);
	__count_vm_event(PGFREE);

	/*
	 * We only track unmovable, reclaimable and movable on pcp lists.
	 * Free ISOLATE pages back to the allocator because they are being
	 * offlined but treat RESERVE as movable pages so we can get those
	 * areas back if necessary. Otherwise, we may have to free
	 * excessively into the page allocator
	 */
	if (migratetype >= MIGRATE_PCPTYPES) {
		if (unlikely(migratetype == MIGRATE_ISOLATE)) {
			free_one_page(zone, page, 0, migratetype);
			goto out;
		}
		migratetype = MIGRATE_MOVABLE;
	}

	if (cold)
		list_add_tail(&page->lru, &pcp->lists[migratetype]);
	else
		list_add(&page->lru, &pcp->lists[migratetype]);
	pcp->count++;
	if (pcp->count >= pcp->high) {
		free_pcppages_bulk(zone, pcp->batch, pcp);
		pcp->count -= pcp->batch;
	}

out:
	local_irq_restore(flags);
	put_cpu();
}