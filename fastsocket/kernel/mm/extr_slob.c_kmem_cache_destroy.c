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
struct kmem_cache {int flags; } ;

/* Variables and functions */
 int SLAB_DESTROY_BY_RCU ; 
 int /*<<< orphan*/  kmemleak_free (struct kmem_cache*) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  slob_free (struct kmem_cache*,int) ; 

void kmem_cache_destroy(struct kmem_cache *c)
{
	kmemleak_free(c);
	if (c->flags & SLAB_DESTROY_BY_RCU)
		rcu_barrier();
	slob_free(c, sizeof(struct kmem_cache));
}