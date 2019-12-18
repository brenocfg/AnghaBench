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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_SLAB_BUG_MASK ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int try_release_extent_buffer (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btree_releasepage(struct page *page, gfp_t gfp_flags)
{
	if (PageWriteback(page) || PageDirty(page))
		return 0;
	/*
	 * We need to mask out eg. __GFP_HIGHMEM and __GFP_DMA32 as we're doing
	 * slab allocation from alloc_extent_state down the callchain where
	 * it'd hit a BUG_ON as those flags are not allowed.
	 */
	gfp_flags &= ~GFP_SLAB_BUG_MASK;

	return try_release_extent_buffer(page, gfp_flags);
}