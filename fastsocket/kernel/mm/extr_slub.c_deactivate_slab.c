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
struct page {void** freelist; int /*<<< orphan*/  inuse; } ;
struct kmem_cache_cpu {void** freelist; size_t offset; struct page* page; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEACTIVATE_REMOTE_FREES ; 
 int /*<<< orphan*/  stat (struct kmem_cache_cpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unfreeze_slab (struct kmem_cache*,struct page*,int) ; 
 scalar_t__ unlikely (void**) ; 

__attribute__((used)) static void deactivate_slab(struct kmem_cache *s, struct kmem_cache_cpu *c)
{
	struct page *page = c->page;
	int tail = 1;

	if (page->freelist)
		stat(c, DEACTIVATE_REMOTE_FREES);
	/*
	 * Merge cpu freelist into slab freelist. Typically we get here
	 * because both freelists are empty. So this is unlikely
	 * to occur.
	 */
	while (unlikely(c->freelist)) {
		void **object;

		tail = 0;	/* Hot objects. Put the slab first */

		/* Retrieve object from cpu_freelist */
		object = c->freelist;
		c->freelist = c->freelist[c->offset];

		/* And put onto the regular freelist */
		object[c->offset] = page->freelist;
		page->freelist = object;
		page->inuse--;
	}
	c->page = NULL;
	unfreeze_slab(s, page, tail);
}