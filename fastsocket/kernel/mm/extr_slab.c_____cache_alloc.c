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
struct kmem_cache {int dummy; } ;
struct array_cache {size_t avail; int touched; void** entry; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_INC_ALLOCHIT (struct kmem_cache*) ; 
 int /*<<< orphan*/  STATS_INC_ALLOCMISS (struct kmem_cache*) ; 
 void* cache_alloc_refill (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_irq_off () ; 
 struct array_cache* cpu_cache_get (struct kmem_cache*) ; 
 int /*<<< orphan*/  kmemleak_erase (void**) ; 
 scalar_t__ likely (size_t) ; 

__attribute__((used)) static inline void *____cache_alloc(struct kmem_cache *cachep, gfp_t flags)
{
	void *objp;
	struct array_cache *ac;

	check_irq_off();

	ac = cpu_cache_get(cachep);
	if (likely(ac->avail)) {
		STATS_INC_ALLOCHIT(cachep);
		ac->touched = 1;
		objp = ac->entry[--ac->avail];
	} else {
		STATS_INC_ALLOCMISS(cachep);
		objp = cache_alloc_refill(cachep, flags);
		/*
		 * the 'ac' may be updated by cache_alloc_refill(),
		 * and kmemleak_erase() requires its correct value.
		 */
		ac = cpu_cache_get(cachep);
	}
	/*
	 * To avoid a false negative, if an object that is in one of the
	 * per-CPU caches is leaked, we need to make sure kmemleak doesn't
	 * treat the array pointers as a reference to the object.
	 */
	kmemleak_erase(&ac->entry[ac->avail]);
	return objp;
}