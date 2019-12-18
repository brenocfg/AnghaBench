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
struct page {int /*<<< orphan*/  lru; } ;
struct kmem_cache_node {int /*<<< orphan*/  nr_partial; } ;

/* Variables and functions */
 int /*<<< orphan*/  __SetPageSlubFrozen (struct page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ slab_trylock (struct page*) ; 

__attribute__((used)) static inline int lock_and_freeze_slab(struct kmem_cache_node *n,
							struct page *page)
{
	if (slab_trylock(page)) {
		list_del(&page->lru);
		n->nr_partial--;
		__SetPageSlubFrozen(page);
		return 1;
	}
	return 0;
}