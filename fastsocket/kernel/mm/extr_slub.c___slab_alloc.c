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
struct page {void** freelist; int /*<<< orphan*/  inuse; int /*<<< orphan*/  objects; } ;
struct kmem_cache_cpu {size_t offset; int node; struct page* page; void* freelist; } ;
struct kmem_cache {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_FROM_PARTIAL ; 
 int /*<<< orphan*/  ALLOC_REFILL ; 
 int /*<<< orphan*/  ALLOC_SLAB ; 
 int /*<<< orphan*/  ALLOC_SLOWPATH ; 
 scalar_t__ PageSlubDebug (struct page*) ; 
 scalar_t__ SLABDEBUG ; 
 int __GFP_NOWARN ; 
 int __GFP_WAIT ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __SetPageSlubFrozen (struct page*) ; 
 int /*<<< orphan*/  alloc_debug_processing (struct kmem_cache*,struct page*,void**,unsigned long) ; 
 int /*<<< orphan*/  deactivate_slab (struct kmem_cache*,struct kmem_cache_cpu*) ; 
 int /*<<< orphan*/  flush_slab (struct kmem_cache*,struct kmem_cache_cpu*) ; 
 struct kmem_cache_cpu* get_cpu_slab (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 struct page* get_partial (struct kmem_cache*,int,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct page* new_slab (struct kmem_cache*,int,int) ; 
 int /*<<< orphan*/  node_match (struct kmem_cache_cpu*,int) ; 
 int page_to_nid (struct page*) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  slab_lock (struct page*) ; 
 int /*<<< orphan*/  slab_out_of_memory (struct kmem_cache*,int,int) ; 
 int /*<<< orphan*/  slab_unlock (struct page*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stat (struct kmem_cache_cpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *__slab_alloc(struct kmem_cache *s, gfp_t gfpflags, int node,
			  unsigned long addr, struct kmem_cache_cpu *c)
{
	void **object;
	struct page *new;

	/* We handle __GFP_ZERO in the caller */
	gfpflags &= ~__GFP_ZERO;

	if (!c->page)
		goto new_slab;

	slab_lock(c->page);
	if (unlikely(!node_match(c, node)))
		goto another_slab;

	stat(c, ALLOC_REFILL);

load_freelist:
	object = c->page->freelist;
	if (unlikely(!object))
		goto another_slab;
	if (unlikely(SLABDEBUG && PageSlubDebug(c->page)))
		goto debug;

	c->freelist = object[c->offset];
	c->page->inuse = c->page->objects;
	c->page->freelist = NULL;
	c->node = page_to_nid(c->page);
unlock_out:
	slab_unlock(c->page);
	stat(c, ALLOC_SLOWPATH);
	return object;

another_slab:
	deactivate_slab(s, c);

new_slab:
	new = get_partial(s, gfpflags, node);
	if (new) {
		c->page = new;
		stat(c, ALLOC_FROM_PARTIAL);
		goto load_freelist;
	}

	if (gfpflags & __GFP_WAIT)
		local_irq_enable();

	new = new_slab(s, gfpflags, node);

	if (gfpflags & __GFP_WAIT)
		local_irq_disable();

	if (new) {
		c = get_cpu_slab(s, smp_processor_id());
		stat(c, ALLOC_SLAB);
		if (c->page)
			flush_slab(s, c);
		slab_lock(new);
		__SetPageSlubFrozen(new);
		c->page = new;
		goto load_freelist;
	}
	if (!(gfpflags & __GFP_NOWARN) && printk_ratelimit())
		slab_out_of_memory(s, gfpflags, node);
	return NULL;
debug:
	if (!alloc_debug_processing(s, c->page, object, addr))
		goto another_slab;

	c->page->inuse++;
	c->page->freelist = object[c->offset];
	c->node = -1;
	goto unlock_out;
}