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
struct page {struct kmem_cache* slab; } ;
struct kmem_cache {int flags; size_t objsize; size_t inuse; size_t size; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int SLAB_DESTROY_BY_RCU ; 
 int SLAB_POISON ; 
 int SLAB_RED_ZONE ; 
 int SLAB_STORE_USER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void const* ZERO_SIZE_PTR ; 
 size_t compound_order (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void const*) ; 

size_t ksize(const void *object)
{
	struct page *page;
	struct kmem_cache *s;

	if (unlikely(object == ZERO_SIZE_PTR))
		return 0;

	page = virt_to_head_page(object);

	if (unlikely(!PageSlab(page))) {
		WARN_ON(!PageCompound(page));
		return PAGE_SIZE << compound_order(page);
	}
	s = page->slab;

#ifdef CONFIG_SLUB_DEBUG
	/*
	 * Debugging requires use of the padding between object
	 * and whatever may come after it.
	 */
	if (s->flags & (SLAB_RED_ZONE | SLAB_POISON))
		return s->objsize;

#endif
	/*
	 * If we have the need to store the freelist pointer
	 * back there or track user information then we can
	 * only use the space before that information.
	 */
	if (s->flags & (SLAB_DESTROY_BY_RCU | SLAB_STORE_USER))
		return s->inuse;
	/*
	 * Else we can use all the padding etc for the allocation
	 */
	return s->size;
}