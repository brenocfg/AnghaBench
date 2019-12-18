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
struct kmem_cache {int flags; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SLAB_DESTROY_BY_RCU ; 
 scalar_t__ __cache_shrink (struct kmem_cache*) ; 
 int /*<<< orphan*/  __kmem_cache_destroy (struct kmem_cache*) ; 
 int /*<<< orphan*/  cache_chain ; 
 int /*<<< orphan*/  cache_chain_mutex ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  slab_error (struct kmem_cache*,char*) ; 
 scalar_t__ unlikely (int) ; 

void kmem_cache_destroy(struct kmem_cache *cachep)
{
	BUG_ON(!cachep || in_interrupt());

	/* Find the cache in the chain of caches. */
	get_online_cpus();
	mutex_lock(&cache_chain_mutex);
	/*
	 * the chain is never empty, cache_cache is never destroyed
	 */
	list_del(&cachep->next);
	if (__cache_shrink(cachep)) {
		slab_error(cachep, "Can't free all objects");
		list_add(&cachep->next, &cache_chain);
		mutex_unlock(&cache_chain_mutex);
		put_online_cpus();
		return;
	}

	if (unlikely(cachep->flags & SLAB_DESTROY_BY_RCU))
		rcu_barrier();

	__kmem_cache_destroy(cachep);
	mutex_unlock(&cache_chain_mutex);
	put_online_cpus();
}