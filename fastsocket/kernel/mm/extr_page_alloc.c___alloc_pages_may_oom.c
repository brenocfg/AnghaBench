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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int gfp_t ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;

/* Variables and functions */
 int ALLOC_CPUSET ; 
 int ALLOC_WMARK_HIGH ; 
 unsigned int PAGE_ALLOC_COSTLY_ORDER ; 
 int __GFP_HARDWALL ; 
 int __GFP_NOFAIL ; 
 int __GFP_THISNODE ; 
 int /*<<< orphan*/  clear_zonelist_oom (struct zonelist*,int) ; 
 struct page* get_page_from_freelist (int,int /*<<< orphan*/ *,unsigned int,struct zonelist*,int,int,struct zone*,int) ; 
 int /*<<< orphan*/  out_of_memory (struct zonelist*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  try_set_zonelist_oom (struct zonelist*,int) ; 

__attribute__((used)) static inline struct page *
__alloc_pages_may_oom(gfp_t gfp_mask, unsigned int order,
	struct zonelist *zonelist, enum zone_type high_zoneidx,
	nodemask_t *nodemask, struct zone *preferred_zone,
	int migratetype)
{
	struct page *page;

	/* Acquire the OOM killer lock for the zones in zonelist */
	if (!try_set_zonelist_oom(zonelist, gfp_mask)) {
		schedule_timeout_uninterruptible(1);
		return NULL;
	}

	/*
	 * Go through the zonelist yet one more time, keep very high watermark
	 * here, this is only to catch a parallel oom killing, we must fail if
	 * we're still under heavy pressure.
	 */
	page = get_page_from_freelist(gfp_mask|__GFP_HARDWALL, nodemask,
		order, zonelist, high_zoneidx,
		ALLOC_WMARK_HIGH|ALLOC_CPUSET,
		preferred_zone, migratetype);
	if (page)
		goto out;

	if (!(gfp_mask & __GFP_NOFAIL)) {
		/* The OOM killer will not help higher order allocs */
		if (order > PAGE_ALLOC_COSTLY_ORDER)
			goto out;
		/*
		 * GFP_THISNODE contains __GFP_NORETRY and we never hit this.
		 * Sanity check for bare calls of __GFP_THISNODE, not real OOM.
		 * The caller should handle page allocation failure by itself if
		 * it specifies __GFP_THISNODE.
		 * Note: Hugepage uses it but will hit PAGE_ALLOC_COSTLY_ORDER.
		 */
		if (gfp_mask & __GFP_THISNODE)
			goto out;
	}
	/* Exhausted what can be done so it's blamo time */
	out_of_memory(zonelist, gfp_mask, order, nodemask);

out:
	clear_zonelist_oom(zonelist, gfp_mask);
	return page;
}