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
struct rcu_head {int dummy; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct kmem_cache {int flags; } ;

/* Variables and functions */
 int SLAB_DESTROY_BY_RCU ; 
 int /*<<< orphan*/  __free_slab (struct kmem_cache*,struct page*) ; 
 int /*<<< orphan*/  call_rcu (struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_free_slab ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void free_slab(struct kmem_cache *s, struct page *page)
{
	if (unlikely(s->flags & SLAB_DESTROY_BY_RCU)) {
		/*
		 * RCU free overloads the RCU head over the LRU
		 */
		struct rcu_head *head = (void *)&page->lru;

		call_rcu(head, rcu_free_slab);
	} else
		__free_slab(s, page);
}