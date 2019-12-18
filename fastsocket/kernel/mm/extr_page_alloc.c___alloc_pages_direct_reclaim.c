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
struct task_struct {int /*<<< orphan*/  flags; struct reclaim_state* reclaim_state; } ;
struct reclaim_state {scalar_t__ reclaimed_slab; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 int /*<<< orphan*/  PF_MEMALLOC ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpuset_memory_pressure_bump () ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  drain_all_pages () ; 
 struct page* get_page_from_freelist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,struct zonelist*,int,int,struct zone*,int) ; 
 int /*<<< orphan*/  lockdep_clear_current_reclaim_state () ; 
 int /*<<< orphan*/  lockdep_set_current_reclaim_state (int /*<<< orphan*/ ) ; 
 unsigned long try_to_free_pages (struct zonelist*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct page *
__alloc_pages_direct_reclaim(gfp_t gfp_mask, unsigned int order,
	struct zonelist *zonelist, enum zone_type high_zoneidx,
	nodemask_t *nodemask, int alloc_flags, struct zone *preferred_zone,
	int migratetype, unsigned long *did_some_progress)
{
	struct page *page = NULL;
	struct reclaim_state reclaim_state;
	struct task_struct *p = current;
	bool drained = false;

	cond_resched();

	/* We now go into synchronous reclaim */
	cpuset_memory_pressure_bump();
	p->flags |= PF_MEMALLOC;
	lockdep_set_current_reclaim_state(gfp_mask);
	reclaim_state.reclaimed_slab = 0;
	p->reclaim_state = &reclaim_state;

	*did_some_progress = try_to_free_pages(zonelist, order, gfp_mask, nodemask);

	p->reclaim_state = NULL;
	lockdep_clear_current_reclaim_state();
	p->flags &= ~PF_MEMALLOC;

	cond_resched();

	if (order != 0)
		drain_all_pages();

	if (unlikely(!(*did_some_progress)))
		return NULL;

retry:
	page = get_page_from_freelist(gfp_mask, nodemask, order,
					zonelist, high_zoneidx,
					alloc_flags, preferred_zone,
					migratetype);

	/*
	 * If an allocation failed after direct reclaim, it could be because
	 * pages are pinned on the per-cpu lists. Drain them and try again
	 */
	if (!page && !drained) {
		drain_all_pages();
		drained = true;
		goto retry;
	}

	return page;
}