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
struct slab_rcu {int /*<<< orphan*/  addr; struct kmem_cache* cachep; } ;
struct rcu_head {int dummy; } ;
struct kmem_cache {int /*<<< orphan*/  slabp_cache; } ;

/* Variables and functions */
 scalar_t__ OFF_SLAB (struct kmem_cache*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct slab_rcu*) ; 
 int /*<<< orphan*/  kmem_freepages (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kmem_rcu_free(struct rcu_head *head)
{
	struct slab_rcu *slab_rcu = (struct slab_rcu *)head;
	struct kmem_cache *cachep = slab_rcu->cachep;

	kmem_freepages(cachep, slab_rcu->addr);
	if (OFF_SLAB(cachep))
		kmem_cache_free(cachep->slabp_cache, slab_rcu);
}