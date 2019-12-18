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
struct zone_reclaim_stat {unsigned long* recent_scanned; unsigned long* recent_rotated; } ;
struct zone {unsigned long pages_scanned; int /*<<< orphan*/  lru_lock; } ;
struct scan_control {int order; int /*<<< orphan*/  target_mem_cgroup; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct mem_cgroup_zone {struct zone* zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPACTION_BUILD ; 
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int /*<<< orphan*/  ISOLATE_ACTIVE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ LRU_ACTIVE ; 
 scalar_t__ LRU_BASE ; 
 int LRU_FILE ; 
 scalar_t__ NR_ACTIVE_ANON ; 
 scalar_t__ NR_ACTIVE_FILE ; 
 scalar_t__ NR_ISOLATED_ANON ; 
 int /*<<< orphan*/  PGREFILL ; 
 unsigned long VM_EXEC ; 
 int /*<<< orphan*/  __count_zone_vm_events (int /*<<< orphan*/ ,struct zone*,unsigned long) ; 
 int /*<<< orphan*/  __mod_zone_page_state (struct zone*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct zone_reclaim_stat* get_reclaim_stat (struct mem_cgroup_zone*) ; 
 scalar_t__ global_reclaim (struct scan_control*) ; 
 scalar_t__ hpage_nr_pages (struct page*) ; 
 unsigned long isolate_pages (unsigned long,struct mem_cgroup_zone*,int /*<<< orphan*/ *,unsigned long*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  l_active ; 
 int /*<<< orphan*/  l_hold ; 
 int /*<<< orphan*/  l_inactive ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 struct page* lru_to_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_active_pages_to_lru (struct zone*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  page_evictable (struct page*,int /*<<< orphan*/ *) ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 scalar_t__ page_referenced (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_pagereclaim_shrinkactive (unsigned long,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void shrink_active_list(unsigned long nr_pages,
			       struct mem_cgroup_zone *mz,
			       struct scan_control *sc,
			       int priority, int file)
{
	unsigned long nr_taken;
	unsigned long pgscanned;
	unsigned long vm_flags;
	LIST_HEAD(l_hold);	/* The pages which were snipped off */
	LIST_HEAD(l_active);
	LIST_HEAD(l_inactive);
	struct page *page;
	struct zone_reclaim_stat *reclaim_stat = get_reclaim_stat(mz);
	unsigned long nr_rotated = 0;
	int order = 0;
	struct zone *zone = mz->zone;

	if (!COMPACTION_BUILD)
		order = sc->order;

	lru_add_drain();
	spin_lock_irq(&zone->lru_lock);

	nr_taken = isolate_pages(nr_pages, mz, &l_hold,
				 &pgscanned, order,
				 ISOLATE_ACTIVE, 1, file);

	if (global_reclaim(sc))
		zone->pages_scanned += pgscanned;

	reclaim_stat->recent_scanned[file] += nr_taken;

	__count_zone_vm_events(PGREFILL, zone, pgscanned);
	if (file)
		__mod_zone_page_state(zone, NR_ACTIVE_FILE, -nr_taken);
	else
		__mod_zone_page_state(zone, NR_ACTIVE_ANON, -nr_taken);
	__mod_zone_page_state(zone, NR_ISOLATED_ANON + file, nr_taken);
	spin_unlock_irq(&zone->lru_lock);

	while (!list_empty(&l_hold)) {
		cond_resched();
		page = lru_to_page(&l_hold);
		list_del(&page->lru);

		if (unlikely(!page_evictable(page, NULL))) {
			putback_lru_page(page);
			continue;
		}

		if (page_referenced(page, 0, sc->target_mem_cgroup,
				    &vm_flags)) {
			nr_rotated += hpage_nr_pages(page);
			/*
			 * Identify referenced, file-backed active pages and
			 * give them one more trip around the active list. So
			 * that executable code get better chances to stay in
			 * memory under moderate memory pressure.  Anon pages
			 * are not likely to be evicted by use-once streaming
			 * IO, plus JVM can create lots of anon VM_EXEC pages,
			 * so we ignore them here.
			 */
			if ((vm_flags & VM_EXEC) && page_is_file_cache(page)) {
				list_add(&page->lru, &l_active);
				continue;
			}
		}

		ClearPageActive(page);	/* we are de-activating */
		list_add(&page->lru, &l_inactive);
	}

	/*
	 * Move pages back to the lru list.
	 */
	spin_lock_irq(&zone->lru_lock);
	/*
	 * Count referenced pages from currently used mappings as rotated,
	 * even though only some of them are actually re-activated.  This
	 * helps balance scan pressure between file and anonymous pages in
	 * get_scan_ratio.
	 */
	reclaim_stat->recent_rotated[file] += nr_rotated;

	move_active_pages_to_lru(zone, &l_active,
						LRU_ACTIVE + file * LRU_FILE);
	move_active_pages_to_lru(zone, &l_inactive,
						LRU_BASE   + file * LRU_FILE);
	__mod_zone_page_state(zone, NR_ISOLATED_ANON + file, -nr_taken);
	spin_unlock_irq(&zone->lru_lock);
	trace_mm_pagereclaim_shrinkactive(pgscanned, file, priority);  
}