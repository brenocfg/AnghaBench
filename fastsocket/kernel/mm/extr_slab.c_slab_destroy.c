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
struct slab_rcu {int /*<<< orphan*/  head; void* addr; struct kmem_cache* cachep; } ;
struct slab {int /*<<< orphan*/  colouroff; int /*<<< orphan*/  s_mem; } ;
struct kmem_cache {int flags; int /*<<< orphan*/  slabp_cache; } ;

/* Variables and functions */
 scalar_t__ OFF_SLAB (struct kmem_cache*) ; 
 int SLAB_DESTROY_BY_RCU ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct slab*) ; 
 int /*<<< orphan*/  kmem_freepages (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  kmem_rcu_free ; 
 int /*<<< orphan*/  slab_destroy_debugcheck (struct kmem_cache*,struct slab*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void slab_destroy(struct kmem_cache *cachep, struct slab *slabp)
{
	void *addr = slabp->s_mem - slabp->colouroff;

	slab_destroy_debugcheck(cachep, slabp);
	if (unlikely(cachep->flags & SLAB_DESTROY_BY_RCU)) {
		struct slab_rcu *slab_rcu;

		slab_rcu = (struct slab_rcu *)slabp;
		slab_rcu->cachep = cachep;
		slab_rcu->addr = addr;
		call_rcu(&slab_rcu->head, kmem_rcu_free);
	} else {
		kmem_freepages(cachep, addr);
		if (OFF_SLAB(cachep))
			kmem_cache_free(cachep->slabp_cache, slabp);
	}
}