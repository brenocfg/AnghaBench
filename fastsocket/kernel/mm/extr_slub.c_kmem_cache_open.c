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
struct kmem_cache {char const* name; void (* ctor ) (void*) ;size_t objsize; size_t align; size_t size; int refcount; int remote_node_defrag_ratio; scalar_t__ offset; int /*<<< orphan*/  oo; int /*<<< orphan*/  flags; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_METADATA_FLAGS ; 
 unsigned long SLAB_PANIC ; 
 int SLUB_DMA ; 
 scalar_t__ alloc_kmem_cache_cpus (struct kmem_cache*,int) ; 
 int /*<<< orphan*/  calculate_sizes (struct kmem_cache*,int) ; 
 scalar_t__ disable_higher_order_debug ; 
 int /*<<< orphan*/  free_kmem_cache_nodes (struct kmem_cache*) ; 
 scalar_t__ get_order (size_t) ; 
 int /*<<< orphan*/  ilog2 (size_t) ; 
 int /*<<< orphan*/  init_kmem_cache_nodes (struct kmem_cache*,int) ; 
 int /*<<< orphan*/  kmem_cache_flags (size_t,unsigned long,char const*,void (*) (void*)) ; 
 int /*<<< orphan*/  kmem_size ; 
 int /*<<< orphan*/  memset (struct kmem_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oo_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,char const*,unsigned long,size_t,int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  set_min_partial (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmem_cache_open(struct kmem_cache *s, gfp_t gfpflags,
		const char *name, size_t size,
		size_t align, unsigned long flags,
		void (*ctor)(void *))
{
	memset(s, 0, kmem_size);
	s->name = name;
	s->ctor = ctor;
	s->objsize = size;
	s->align = align;
	s->flags = kmem_cache_flags(size, flags, name, ctor);

	if (!calculate_sizes(s, -1))
		goto error;
	if (disable_higher_order_debug) {
		/*
		 * Disable debugging flags that store metadata if the min slab
		 * order increased.
		 */
		if (get_order(s->size) > get_order(s->objsize)) {
			s->flags &= ~DEBUG_METADATA_FLAGS;
			s->offset = 0;
			if (!calculate_sizes(s, -1))
				goto error;
		}
	}

	/*
	 * The larger the object size is, the more pages we want on the partial
	 * list to avoid pounding the page allocator excessively.
	 */
	set_min_partial(s, ilog2(s->size));
	s->refcount = 1;
#ifdef CONFIG_NUMA
	s->remote_node_defrag_ratio = 1000;
#endif
	if (!init_kmem_cache_nodes(s, gfpflags & ~SLUB_DMA))
		goto error;

	if (alloc_kmem_cache_cpus(s, gfpflags & ~SLUB_DMA))
		return 1;
	free_kmem_cache_nodes(s);
error:
	if (flags & SLAB_PANIC)
		panic("Cannot create slab %s size=%lu realsize=%u "
			"order=%u offset=%u flags=%lx\n",
			s->name, (unsigned long)size, s->size, oo_order(s->oo),
			s->offset, flags);
	return 0;
}