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
struct slab {scalar_t__ inuse; int /*<<< orphan*/  list; } ;
struct kmem_list3 {scalar_t__ free_objects; scalar_t__ free_limit; int /*<<< orphan*/  slabs_partial; int /*<<< orphan*/  slabs_free; } ;
struct kmem_cache {scalar_t__ num; struct kmem_list3** nodelists; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_DEC_ACTIVE (struct kmem_cache*) ; 
 int /*<<< orphan*/  check_slabp (struct kmem_cache*,struct slab*) ; 
 int /*<<< orphan*/  check_spinlock_acquired_node (struct kmem_cache*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slab_destroy (struct kmem_cache*,struct slab*) ; 
 int /*<<< orphan*/  slab_put_obj (struct kmem_cache*,struct slab*,void*,int) ; 
 struct slab* virt_to_slab (void*) ; 

__attribute__((used)) static void free_block(struct kmem_cache *cachep, void **objpp, int nr_objects,
		       int node)
{
	int i;
	struct kmem_list3 *l3;

	for (i = 0; i < nr_objects; i++) {
		void *objp = objpp[i];
		struct slab *slabp;

		slabp = virt_to_slab(objp);
		l3 = cachep->nodelists[node];
		list_del(&slabp->list);
		check_spinlock_acquired_node(cachep, node);
		check_slabp(cachep, slabp);
		slab_put_obj(cachep, slabp, objp, node);
		STATS_DEC_ACTIVE(cachep);
		l3->free_objects++;
		check_slabp(cachep, slabp);

		/* fixup slab chains */
		if (slabp->inuse == 0) {
			if (l3->free_objects > l3->free_limit) {
				l3->free_objects -= cachep->num;
				/* No need to drop any previously held
				 * lock here, even if we have a off-slab slab
				 * descriptor it is guaranteed to come from
				 * a different cache, refer to comments before
				 * alloc_slabmgmt.
				 */
				slab_destroy(cachep, slabp);
			} else {
				list_add(&slabp->list, &l3->slabs_free);
			}
		} else {
			/* Unconditionally move a slab to the end of the
			 * partial list on free - maximum time for the
			 * other objects to be freed, too.
			 */
			list_add_tail(&slabp->list, &l3->slabs_partial);
		}
	}
}