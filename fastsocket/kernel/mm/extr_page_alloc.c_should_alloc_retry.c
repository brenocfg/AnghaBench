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
typedef  int gfp_t ;

/* Variables and functions */
 unsigned int PAGE_ALLOC_COSTLY_ORDER ; 
 int __GFP_NOFAIL ; 
 int __GFP_NORETRY ; 
 int __GFP_REPEAT ; 

__attribute__((used)) static inline int
should_alloc_retry(gfp_t gfp_mask, unsigned int order,
				unsigned long pages_reclaimed)
{
	/* Do not loop if specifically requested */
	if (gfp_mask & __GFP_NORETRY)
		return 0;

	/*
	 * In this implementation, order <= PAGE_ALLOC_COSTLY_ORDER
	 * means __GFP_NOFAIL, but that may not be true in other
	 * implementations.
	 */
	if (order <= PAGE_ALLOC_COSTLY_ORDER)
		return 1;

	/*
	 * For order > PAGE_ALLOC_COSTLY_ORDER, if __GFP_REPEAT is
	 * specified, then we retry until we no longer reclaim any pages
	 * (above), or we've reclaimed an order of pages at least as
	 * large as the allocation's order. In both cases, if the
	 * allocation still fails, we stop retrying.
	 */
	if (gfp_mask & __GFP_REPEAT && pages_reclaimed < (1 << order))
		return 1;

	/*
	 * Don't let big-order allocations loop unless the caller
	 * explicitly requests that.
	 */
	if (gfp_mask & __GFP_NOFAIL)
		return 1;

	return 0;
}