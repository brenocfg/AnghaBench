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
struct zonelist {int dummy; } ;
struct zone {int dummy; } ;
struct task_struct {int flags; int /*<<< orphan*/  comm; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int gfp_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 int ALLOC_NO_WATERMARKS ; 
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int GFP_THISNODE ; 
 int HZ ; 
 unsigned int MAX_ORDER ; 
 scalar_t__ NUMA_BUILD ; 
 unsigned int PAGE_ALLOC_COSTLY_ORDER ; 
 int PF_EXITING ; 
 int PF_MEMALLOC ; 
 unsigned int SHOW_MEM_FILTER_NODES ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_FS ; 
 int __GFP_NOFAIL ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int __GFP_NO_KSWAPD ; 
 int __GFP_WAIT ; 
 struct page* __alloc_pages_direct_compact (int,unsigned int,struct zonelist*,int,int /*<<< orphan*/ *,int,struct zone*,int,int,int*,int*,unsigned long*) ; 
 struct page* __alloc_pages_direct_reclaim (int,unsigned int,struct zonelist*,int,int /*<<< orphan*/ *,int,struct zone*,int,unsigned long*) ; 
 struct page* __alloc_pages_high_priority (int,unsigned int,struct zonelist*,int,int /*<<< orphan*/ *,struct zone*,int) ; 
 struct page* __alloc_pages_may_oom (int,unsigned int,struct zonelist*,int,int /*<<< orphan*/ *,struct zone*,int) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  dump_stack () ; 
 struct page* get_page_from_freelist (int,int /*<<< orphan*/ *,unsigned int,struct zonelist*,int,int,struct zone*,int) ; 
 int gfp_to_alloc_flags (int) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ kmemcheck_enabled ; 
 int /*<<< orphan*/  kmemcheck_pagealloc_alloc (struct page*,unsigned int,int) ; 
 scalar_t__ oom_killer_disabled ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ printk_ratelimit () ; 
 scalar_t__ should_alloc_retry (int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  should_suppress_show_mem () ; 
 int /*<<< orphan*/  show_mem (unsigned int) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_iff_congested (struct zone*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_all_kswapd (unsigned int,struct zonelist*,int) ; 

__attribute__((used)) static inline struct page *
__alloc_pages_slowpath(gfp_t gfp_mask, unsigned int order,
	struct zonelist *zonelist, enum zone_type high_zoneidx,
	nodemask_t *nodemask, struct zone *preferred_zone,
	int migratetype)
{
	const gfp_t wait = gfp_mask & __GFP_WAIT;
	struct page *page = NULL;
	int alloc_flags;
	unsigned long pages_reclaimed = 0;
	unsigned long did_some_progress;
	struct task_struct *p = current;
	bool sync_migration = false;
	bool deferred_compaction = false;
	bool contended_compaction = false;

	/*
	 * In the slowpath, we sanity check order to avoid ever trying to
	 * reclaim >= MAX_ORDER areas which will never succeed. Callers may
	 * be using allocators in order of preference for an area that is
	 * too large.
	 */
	if (order >= MAX_ORDER) {
		WARN_ON_ONCE(!(gfp_mask & __GFP_NOWARN));
		return NULL;
	}

	/*
	 * GFP_THISNODE (meaning __GFP_THISNODE, __GFP_NORETRY and
	 * __GFP_NOWARN set) should not cause reclaim since the subsystem
	 * (f.e. slab) using GFP_THISNODE may choose to trigger reclaim
	 * using a larger set of nodes after it has established that the
	 * allowed per node queues are empty and that nodes are
	 * over allocated.
	 */
	if (NUMA_BUILD && (gfp_mask & GFP_THISNODE) == GFP_THISNODE)
		goto nopage;

restart:
	if (!(gfp_mask & __GFP_NO_KSWAPD))
		wake_all_kswapd(order, zonelist, high_zoneidx);

	/*
	 * OK, we're below the kswapd watermark and have kicked background
	 * reclaim. Now things get more complex, so set up alloc_flags according
	 * to how we want to proceed.
	 */
	alloc_flags = gfp_to_alloc_flags(gfp_mask);

	/* This is the last chance, in general, before the goto nopage. */
	page = get_page_from_freelist(gfp_mask, nodemask, order, zonelist,
			high_zoneidx, alloc_flags & ~ALLOC_NO_WATERMARKS,
			preferred_zone, migratetype);
	if (page)
		goto got_pg;

rebalance:
	/* Allocate without watermarks if the context allows */
	if (alloc_flags & ALLOC_NO_WATERMARKS) {
		page = __alloc_pages_high_priority(gfp_mask, order,
				zonelist, high_zoneidx, nodemask,
				preferred_zone, migratetype);
		if (page)
			goto got_pg;
	}

	/* Atomic allocations - we can't balance anything */
	if (!wait)
		goto nopage;

	/* Avoid recursion of direct reclaim */
	if (p->flags & PF_MEMALLOC)
		goto nopage;

	/* Avoid allocations with no watermarks from looping endlessly */
	if (test_thread_flag(TIF_MEMDIE) && !(gfp_mask & __GFP_NOFAIL))
		goto nopage;

	/*
	 * Try direct compaction. The first pass is asynchronous. Subsequent
	 * attempts after direct reclaim are synchronous
	 */
	page = __alloc_pages_direct_compact(gfp_mask, order,
					zonelist, high_zoneidx,
					nodemask,
					alloc_flags, preferred_zone,
					migratetype, sync_migration,
					&contended_compaction,
					&deferred_compaction,
					&did_some_progress);
	if (page)
		goto got_pg;
	sync_migration = true;

	/*
	 * If compaction is deferred for high-order allocations, it is because
	 * sync compaction recently failed. In this is the case and the caller
	 * requested a movable allocation that does not heavily disrupt the
	 * system then fail the allocation instead of entering direct reclaim.
	 */
	if ((deferred_compaction || contended_compaction) &&
						(gfp_mask & __GFP_NO_KSWAPD))
		goto nopage;

	/* Try direct reclaim and then allocating */
	page = __alloc_pages_direct_reclaim(gfp_mask, order,
					zonelist, high_zoneidx,
					nodemask,
					alloc_flags, preferred_zone,
					migratetype, &did_some_progress);
	if (page)
		goto got_pg;

	/*
	 * If we failed to make any progress reclaiming, then we are
	 * running out of options and have to consider going OOM
	 */
	if (!did_some_progress) {
		if ((gfp_mask & __GFP_FS) && !(gfp_mask & __GFP_NORETRY)) {
			if (oom_killer_disabled)
				goto nopage;
			page = __alloc_pages_may_oom(gfp_mask, order,
					zonelist, high_zoneidx,
					nodemask, preferred_zone,
					migratetype);
			if (page)
				goto got_pg;

			/*
			 * The OOM killer does not trigger for high-order
			 * ~__GFP_NOFAIL allocations so if no progress is being
			 * made, there are no other options and retrying is
			 * unlikely to help.
			 */
			if (order > PAGE_ALLOC_COSTLY_ORDER &&
						!(gfp_mask & __GFP_NOFAIL))
				goto nopage;

			goto restart;
		}
	}

	/* Check if we should retry the allocation */
	pages_reclaimed += did_some_progress;
	if (should_alloc_retry(gfp_mask, order, pages_reclaimed)) {
		/* Too much pressure, back off a bit at let reclaimers do work */
		wait_iff_congested(preferred_zone, BLK_RW_ASYNC, HZ/50);
		goto rebalance;
	} else {
		/*
		 * High-order allocations do not necessarily loop after
		 * direct reclaim and reclaim/compaction depends on compaction
		 * being called after reclaim so call directly if necessary
		 */
		page = __alloc_pages_direct_compact(gfp_mask, order,
					zonelist, high_zoneidx,
					nodemask,
					alloc_flags, preferred_zone,
					migratetype, sync_migration,
					&contended_compaction,
					&deferred_compaction,
					&did_some_progress);
		if (page)
			goto got_pg;
	}

nopage:
	if (!(gfp_mask & __GFP_NOWARN) && printk_ratelimit()) {
		unsigned int filter = SHOW_MEM_FILTER_NODES;

		/*
		 * This documents exceptions given to allocations in certain
		 * contexts that are allowed to allocate outside current's set
		 * of allowed nodes.
		 */
		if (!(gfp_mask & __GFP_NOMEMALLOC))
			if (test_thread_flag(TIF_MEMDIE) ||
			    (current->flags & (PF_MEMALLOC | PF_EXITING)))
				filter &= ~SHOW_MEM_FILTER_NODES;
		if (in_interrupt() || !wait)
			filter &= ~SHOW_MEM_FILTER_NODES;

		pr_warning("%s: page allocation failure. order:%d, mode:0x%x\n",
			p->comm, order, gfp_mask);
		dump_stack();
		if (!should_suppress_show_mem())
			show_mem(filter);
	}
	return page;
got_pg:
	if (kmemcheck_enabled)
		kmemcheck_pagealloc_alloc(page, order, gfp_mask);
	return page;

}