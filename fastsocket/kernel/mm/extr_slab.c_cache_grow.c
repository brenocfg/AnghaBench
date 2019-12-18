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
struct slab {int /*<<< orphan*/  list; } ;
struct kmem_list3 {size_t colour_next; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  free_objects; int /*<<< orphan*/  slabs_free; } ;
struct kmem_cache {size_t colour; size_t colour_off; scalar_t__ num; struct kmem_list3** nodelists; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_CONSTRAINT_MASK ; 
 int GFP_RECLAIM_MASK ; 
 int GFP_SLAB_BUG_MASK ; 
 int /*<<< orphan*/  STATS_INC_GROWN (struct kmem_cache*) ; 
 int __GFP_WAIT ; 
 struct slab* alloc_slabmgmt (struct kmem_cache*,void*,size_t,int,int) ; 
 int /*<<< orphan*/  cache_init_objs (struct kmem_cache*,struct slab*) ; 
 int /*<<< orphan*/  check_irq_off () ; 
 int /*<<< orphan*/  kmem_flagcheck (struct kmem_cache*,int) ; 
 int /*<<< orphan*/  kmem_freepages (struct kmem_cache*,void*) ; 
 void* kmem_getpages (struct kmem_cache*,int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  slab_map_pages (struct kmem_cache*,struct slab*,void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cache_grow(struct kmem_cache *cachep,
		gfp_t flags, int nodeid, void *objp)
{
	struct slab *slabp;
	size_t offset;
	gfp_t local_flags;
	struct kmem_list3 *l3;

	/*
	 * Be lazy and only check for valid flags here,  keeping it out of the
	 * critical path in kmem_cache_alloc().
	 */
	BUG_ON(flags & GFP_SLAB_BUG_MASK);
	local_flags = flags & (GFP_CONSTRAINT_MASK|GFP_RECLAIM_MASK);

	/* Take the l3 list lock to change the colour_next on this node */
	check_irq_off();
	l3 = cachep->nodelists[nodeid];
	spin_lock(&l3->list_lock);

	/* Get colour for the slab, and cal the next value. */
	offset = l3->colour_next;
	l3->colour_next++;
	if (l3->colour_next >= cachep->colour)
		l3->colour_next = 0;
	spin_unlock(&l3->list_lock);

	offset *= cachep->colour_off;

	if (local_flags & __GFP_WAIT)
		local_irq_enable();

	/*
	 * The test for missing atomic flag is performed here, rather than
	 * the more obvious place, simply to reduce the critical path length
	 * in kmem_cache_alloc(). If a caller is seriously mis-behaving they
	 * will eventually be caught here (where it matters).
	 */
	kmem_flagcheck(cachep, flags);

	/*
	 * Get mem for the objs.  Attempt to allocate a physical page from
	 * 'nodeid'.
	 */
	if (!objp)
		objp = kmem_getpages(cachep, local_flags, nodeid);
	if (!objp)
		goto failed;

	/* Get slab management. */
	slabp = alloc_slabmgmt(cachep, objp, offset,
			local_flags & ~GFP_CONSTRAINT_MASK, nodeid);
	if (!slabp)
		goto opps1;

	slab_map_pages(cachep, slabp, objp);

	cache_init_objs(cachep, slabp);

	if (local_flags & __GFP_WAIT)
		local_irq_disable();
	check_irq_off();
	spin_lock(&l3->list_lock);

	/* Make slab active. */
	list_add_tail(&slabp->list, &(l3->slabs_free));
	STATS_INC_GROWN(cachep);
	l3->free_objects += cachep->num;
	spin_unlock(&l3->list_lock);
	return 1;
opps1:
	kmem_freepages(cachep, objp);
failed:
	if (local_flags & __GFP_WAIT)
		local_irq_disable();
	return 0;
}