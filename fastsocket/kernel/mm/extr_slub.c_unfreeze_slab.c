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
struct page {scalar_t__ freelist; scalar_t__ inuse; } ;
struct kmem_cache_node {scalar_t__ nr_partial; } ;
struct kmem_cache_cpu {int dummy; } ;
struct kmem_cache {int flags; scalar_t__ min_partial; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEACTIVATE_EMPTY ; 
 int /*<<< orphan*/  DEACTIVATE_FULL ; 
 int /*<<< orphan*/  DEACTIVATE_TO_HEAD ; 
 int /*<<< orphan*/  DEACTIVATE_TO_TAIL ; 
 int /*<<< orphan*/  FREE_SLAB ; 
 scalar_t__ PageSlubDebug (struct page*) ; 
 scalar_t__ SLABDEBUG ; 
 int SLAB_STORE_USER ; 
 int /*<<< orphan*/  __ClearPageSlubFrozen (struct page*) ; 
 int /*<<< orphan*/  add_full (struct kmem_cache_node*,struct page*) ; 
 int /*<<< orphan*/  add_partial (struct kmem_cache_node*,struct page*,int) ; 
 int /*<<< orphan*/  discard_slab (struct kmem_cache*,struct page*) ; 
 struct kmem_cache_cpu* get_cpu_slab (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 struct kmem_cache_node* get_node (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  slab_unlock (struct page*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stat (struct kmem_cache_cpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unfreeze_slab(struct kmem_cache *s, struct page *page, int tail)
{
	struct kmem_cache_node *n = get_node(s, page_to_nid(page));
	struct kmem_cache_cpu *c = get_cpu_slab(s, smp_processor_id());

	__ClearPageSlubFrozen(page);
	if (page->inuse) {

		if (page->freelist) {
			add_partial(n, page, tail);
			stat(c, tail ? DEACTIVATE_TO_TAIL : DEACTIVATE_TO_HEAD);
		} else {
			stat(c, DEACTIVATE_FULL);
			if (SLABDEBUG && PageSlubDebug(page) &&
						(s->flags & SLAB_STORE_USER))
				add_full(n, page);
		}
		slab_unlock(page);
	} else {
		stat(c, DEACTIVATE_EMPTY);
		if (n->nr_partial < s->min_partial) {
			/*
			 * Adding an empty slab to the partial slabs in order
			 * to avoid page allocator overhead. This slab needs
			 * to come after the other slabs with objects in
			 * so that the others get filled first. That way the
			 * size of the partial list stays small.
			 *
			 * kmem_cache_shrink can reclaim any empty slabs from
			 * the partial list.
			 */
			add_partial(n, page, 1);
			slab_unlock(page);
		} else {
			slab_unlock(page);
			stat(get_cpu_slab(s, raw_smp_processor_id()), FREE_SLAB);
			discard_slab(s, page);
		}
	}
}