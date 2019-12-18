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
struct slob_rcu {int size; int /*<<< orphan*/  head; } ;
struct kmem_cache {int flags; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_RCU_HEAD (int /*<<< orphan*/ *) ; 
 int SLAB_DESTROY_BY_RCU ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __kmem_cache_free (void*,int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_rcu_free ; 
 int /*<<< orphan*/  kmemleak_free_recursive (void*,int) ; 
 int /*<<< orphan*/  trace_kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ unlikely (int) ; 

void kmem_cache_free(struct kmem_cache *c, void *b)
{
	kmemleak_free_recursive(b, c->flags);
	if (unlikely(c->flags & SLAB_DESTROY_BY_RCU)) {
		struct slob_rcu *slob_rcu;
		slob_rcu = b + (c->size - sizeof(struct slob_rcu));
		INIT_RCU_HEAD(&slob_rcu->head);
		slob_rcu->size = c->size;
		call_rcu(&slob_rcu->head, kmem_rcu_free);
	} else {
		__kmem_cache_free(b, c->size);
	}

	trace_kmem_cache_free(_RET_IP_, b);
}