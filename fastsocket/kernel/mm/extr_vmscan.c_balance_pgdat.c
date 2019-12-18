#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zone {int present_pages; int pages_scanned; int prev_priority; } ;
struct scan_control {int may_unmap; int may_swap; int order; int nr_reclaimed; int may_writepage; int /*<<< orphan*/  gfp_mask; scalar_t__ nr_scanned; int /*<<< orphan*/ * target_mem_cgroup; int /*<<< orphan*/  swappiness; int /*<<< orphan*/  nr_to_reclaim; } ;
struct reclaim_state {scalar_t__ reclaimed_slab; } ;
struct TYPE_5__ {int nr_zones; int node_id; struct zone* node_zones; } ;
typedef  TYPE_1__ pg_data_t ;
struct TYPE_6__ {struct reclaim_state* reclaim_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int DEF_PRIORITY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  KSWAPD_SKIP_CONGESTION_WAIT ; 
 int KSWAPD_ZONE_BALANCE_GAP_RATIO ; 
 int MAX_NR_ZONES ; 
 int /*<<< orphan*/  PAGEOUTRUN ; 
 int PAGE_ALLOC_COSTLY_ORDER ; 
 int SWAP_CLUSTER_MAX ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  ZONE_ALL_UNRECLAIMABLE ; 
 int /*<<< orphan*/  ZONE_CONGESTED ; 
 int /*<<< orphan*/  age_active_anon (struct zone*,struct scan_control*,int) ; 
 int /*<<< orphan*/  compact_zone_order (struct zone*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  disable_swap_token () ; 
 scalar_t__ high_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  laptop_mode ; 
 int /*<<< orphan*/  low_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  mem_cgroup_soft_limit_reclaim (struct zone*,int,int /*<<< orphan*/ ,int,int) ; 
 unsigned long min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ min_wmark_pages (struct zone*) ; 
 int /*<<< orphan*/  note_zone_scanning_priority (struct zone*,int) ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 
 int shrink_slab (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  shrink_zone (int,struct zone*,struct scan_control*) ; 
 int /*<<< orphan*/  trace_mm_kswapd_ran (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  vm_swappiness ; 
 int /*<<< orphan*/  zone_clear_flag (struct zone*,int /*<<< orphan*/ ) ; 
 int zone_idx (struct zone*) ; 
 scalar_t__ zone_is_all_unreclaimable (struct zone*) ; 
 int zone_reclaimable_pages (struct zone*) ; 
 int /*<<< orphan*/  zone_set_flag (struct zone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_watermark_ok (struct zone*,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_watermark_ok_safe (struct zone*,int,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long balance_pgdat(pg_data_t *pgdat, int order)
{
	int all_zones_ok;
	int priority;
	int i;
	unsigned long total_scanned;
	unsigned long total_reclaimed = 0;
	struct reclaim_state *reclaim_state = current->reclaim_state;
	struct scan_control sc = {
		.gfp_mask = GFP_KERNEL,
		.may_unmap = 1,
		.may_swap = 1,
		/*
		 * kswapd doesn't want to be bailed out while reclaim. because
		 * we want to put equal scanning pressure on each zone.
		 */
		.nr_to_reclaim = ULONG_MAX,
		.swappiness = vm_swappiness,
		.order = order,
		.target_mem_cgroup = NULL,
	};
	/*
	 * temp_priority is used to remember the scanning priority at which
	 * this zone was successfully refilled to
	 * free_pages == high_wmark_pages(zone).
	 */
	int temp_priority[MAX_NR_ZONES];

loop_again:
	total_scanned = 0;
	sc.nr_reclaimed = 0;
	sc.may_writepage = !laptop_mode;
	count_vm_event(PAGEOUTRUN);

	for (i = 0; i < pgdat->nr_zones; i++)
		temp_priority[i] = DEF_PRIORITY;

	for (priority = DEF_PRIORITY; priority >= 0; priority--) {
		int end_zone = 0;	/* Inclusive.  0 = ZONE_DMA */
		unsigned long lru_pages = 0;
		int has_under_min_watermark_zone = 0;

		/* The swap token gets in the way of swapout... */
		if (!priority)
			disable_swap_token();

		all_zones_ok = 1;

		/*
		 * Scan in the highmem->dma direction for the highest
		 * zone which needs scanning
		 */
		for (i = pgdat->nr_zones - 1; i >= 0; i--) {
			struct zone *zone = pgdat->node_zones + i;

			if (!populated_zone(zone))
				continue;

			if (zone_is_all_unreclaimable(zone) &&
			    priority != DEF_PRIORITY)
				continue;

			/*
			 * Do some background aging of the anon list, to give
			 * pages a chance to be referenced before reclaiming.
			 */
			age_active_anon(zone, &sc, priority);

			if (!zone_watermark_ok_safe(zone, order,
					high_wmark_pages(zone), 0, 0)) {
				end_zone = i;
				break;
			}
		}
		if (i < 0)
			goto out;

		for (i = 0; i <= end_zone; i++) {
			struct zone *zone = pgdat->node_zones + i;

			lru_pages += zone_reclaimable_pages(zone);
		}

		/*
		 * Now scan the zone in the dma->highmem direction, stopping
		 * at the last zone which needs scanning.
		 *
		 * We do this because the page allocator works in the opposite
		 * direction.  This prevents the page allocator from allocating
		 * pages behind kswapd's direction of progress, which would
		 * cause too much scanning of the lower zones.
		 */
		for (i = 0; i <= end_zone; i++) {
			struct zone *zone = pgdat->node_zones + i;
			int nr_slab;
			int nid, zid;
			unsigned long balance_gap;
			bool contended = false;

			if (!populated_zone(zone))
				continue;

			if (zone_is_all_unreclaimable(zone) &&
					priority != DEF_PRIORITY)
				continue;

			if (!zone_watermark_ok(zone, order,
					high_wmark_pages(zone), end_zone, 0))
				all_zones_ok = 0;
			temp_priority[i] = priority;
			sc.nr_scanned = 0;
			note_zone_scanning_priority(zone, priority);

			nid = pgdat->node_id;
			zid = zone_idx(zone);
			/*
			 * Call soft limit reclaim before calling shrink_zone.
			 * For now we ignore the return value
			 */
			mem_cgroup_soft_limit_reclaim(zone, order, sc.gfp_mask,
							nid, zid);
			/*
			 * We put equal pressure on every zone, unless
			 * one zone has way too many pages free
			 * already. The "too many pages" is defined
			 * as the high wmark plus a "gap" where the
			 * gap is either the low watermark or 1%
			 * of the zone, whichever is smaller.
			 */
			balance_gap = min(low_wmark_pages(zone),
				(zone->present_pages +
					KSWAPD_ZONE_BALANCE_GAP_RATIO-1) /
				KSWAPD_ZONE_BALANCE_GAP_RATIO);
			if (!zone_watermark_ok_safe(zone, order,
					high_wmark_pages(zone) + balance_gap,
					end_zone, 0))
				shrink_zone(priority, zone, &sc);
			reclaim_state->reclaimed_slab = 0;
			nr_slab = shrink_slab(sc.nr_scanned, GFP_KERNEL,
						lru_pages);
			sc.nr_reclaimed += reclaim_state->reclaimed_slab;
			total_scanned += sc.nr_scanned;

			if (zone_is_all_unreclaimable(zone))
				continue;
			if (nr_slab == 0 && zone->pages_scanned >=
					(zone_reclaimable_pages(zone) * 6))
					zone_set_flag(zone,
						      ZONE_ALL_UNRECLAIMABLE);
			/*
			 * If we've done a decent amount of scanning and
			 * the reclaim ratio is low, start doing writepage
			 * even in laptop mode
			 */
			if (total_scanned > SWAP_CLUSTER_MAX * 2 &&
			    total_scanned > sc.nr_reclaimed + sc.nr_reclaimed / 2)
				sc.may_writepage = 1;

			/*
			 * Compact the zone for higher orders to reduce
			 * latencies for higher-order allocations that
			 * would ordinarily call try_to_compact_pages()
			 */
			if (sc.order > PAGE_ALLOC_COSTLY_ORDER)
				compact_zone_order(zone, sc.order, sc.gfp_mask, 0,
						&contended);

			if (!zone_watermark_ok_safe(zone, order,
					high_wmark_pages(zone), end_zone, 0)) {
				/*
				 * We are still under min water mark. it mean we have
				 * GFP_ATOMIC allocation failure risk. Hurry up!
				 */
				if (!zone_watermark_ok_safe(zone, order,
					    min_wmark_pages(zone), end_zone, 0))
					has_under_min_watermark_zone = 1;
			} else {
				/*
				 * If a zone reaches its high watermark,
				 * consider it to be no longer congested. It's
				 * possible there are dirty pages backed by
				 * congested BDIs but as pressure is relieved,
				 * spectulatively avoid congestion waits
				 */
				zone_clear_flag(zone, ZONE_CONGESTED);
                        }


		}
		total_reclaimed += sc.nr_reclaimed;
		if (all_zones_ok)
			break;		/* kswapd: all done */
		/*
		 * OK, kswapd is getting into trouble.  Take a nap, then take
		 * another pass across the zones.
		 */
		if (total_scanned && (priority < DEF_PRIORITY - 2)) {
			if (has_under_min_watermark_zone)
				count_vm_event(KSWAPD_SKIP_CONGESTION_WAIT);
			else
				congestion_wait(BLK_RW_ASYNC, HZ/10);
		}

		/*
		 * We do this so kswapd doesn't build up large priorities for
		 * example when it is freeing in parallel with allocators. It
		 * matches the direct reclaim path behaviour in terms of impact
		 * on zone->*_priority.
		 */
		if (sc.nr_reclaimed >= SWAP_CLUSTER_MAX)
			break;
		cond_resched();
	}
out:
	/*
	 * Note within each zone the priority level at which this zone was
	 * brought into a happy state.  So that the next thread which scans this
	 * zone will start out at that priority level.
	 */
	for (i = 0; i < pgdat->nr_zones; i++) {
		struct zone *zone = pgdat->node_zones + i;

		zone->prev_priority = temp_priority[i];
	}
	if (!all_zones_ok) {
		cond_resched();

		try_to_freeze();

		/*
		 * Fragmentation may mean that the system cannot be
		 * rebalanced for high-order allocations in all zones.
		 * At this point, if nr_reclaimed < SWAP_CLUSTER_MAX,
		 * it means the zones have been fully scanned and are still
		 * not balanced. For high-order allocations, there is
		 * little point trying all over again as kswapd may
		 * infinite loop.
		 *
		 * Instead, recheck all watermarks at order-0 as they
		 * are the most important. If watermarks are ok, kswapd will go
		 * back to sleep. High-order users can still perform direct
		 * reclaim if they wish.
		 */
		if (sc.nr_reclaimed < SWAP_CLUSTER_MAX)
			order = sc.order = 0;

		goto loop_again;
	}

	trace_mm_kswapd_ran(pgdat, total_reclaimed);
	return sc.nr_reclaimed;
}