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
struct page {int /*<<< orphan*/  objects; } ;
struct kmem_cache_order_objects {int dummy; } ;
struct kmem_cache {int allocflags; int flags; scalar_t__ ctor; struct kmem_cache_order_objects min; struct kmem_cache_order_objects oo; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int DEBUG_DEFAULT_FLAGS ; 
 int /*<<< orphan*/  NR_SLAB_RECLAIMABLE ; 
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int /*<<< orphan*/  ORDER_FALLBACK ; 
 int SLAB_NOTRACK ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int __GFP_NOFAIL ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct page* alloc_slab_page (int,int,struct kmem_cache_order_objects) ; 
 int /*<<< orphan*/  get_cpu_slab (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemcheck_alloc_shadow (struct page*,int,int,int) ; 
 scalar_t__ kmemcheck_enabled ; 
 int /*<<< orphan*/  kmemcheck_mark_unallocated_pages (struct page*,int) ; 
 int /*<<< orphan*/  kmemcheck_mark_uninitialized_pages (struct page*,int) ; 
 int /*<<< orphan*/  mod_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oo_objects (struct kmem_cache_order_objects) ; 
 int oo_order (struct kmem_cache_order_objects) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct page *allocate_slab(struct kmem_cache *s, gfp_t flags, int node)
{
	struct page *page;
	struct kmem_cache_order_objects oo = s->oo;
	gfp_t alloc_gfp;

	flags |= s->allocflags;

	/*
	 * Let the initial higher-order allocation fail under memory pressure
	 * so we fall-back to the minimum order allocation.
	 */
	alloc_gfp = (flags | __GFP_NOWARN | __GFP_NORETRY) & ~__GFP_NOFAIL;

	page = alloc_slab_page(alloc_gfp, node, oo);
	if (unlikely(!page)) {
		oo = s->min;
		/*
		 * Allocation may have failed due to fragmentation.
		 * Try a lower order alloc if possible
		 */
		page = alloc_slab_page(flags, node, oo);
		if (!page)
			return NULL;

		stat(get_cpu_slab(s, raw_smp_processor_id()), ORDER_FALLBACK);
	}

	if (kmemcheck_enabled
		&& !(s->flags & (SLAB_NOTRACK | DEBUG_DEFAULT_FLAGS))) {
		int pages = 1 << oo_order(oo);

		kmemcheck_alloc_shadow(page, oo_order(oo), flags, node);

		/*
		 * Objects from caches that have a constructor don't get
		 * cleared when they're allocated, so we need to do it here.
		 */
		if (s->ctor)
			kmemcheck_mark_uninitialized_pages(page, pages);
		else
			kmemcheck_mark_unallocated_pages(page, pages);
	}

	page->objects = oo_objects(oo);
	mod_zone_page_state(page_zone(page),
		(s->flags & SLAB_RECLAIM_ACCOUNT) ?
		NR_SLAB_RECLAIMABLE : NR_SLAB_UNRECLAIMABLE,
		1 << oo_order(oo));

	return page;
}