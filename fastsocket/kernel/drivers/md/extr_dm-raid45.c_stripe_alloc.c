#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cache; } ;
struct stripe_cache {TYPE_1__ kc; } ;
struct stripe {int /*<<< orphan*/  obj; } ;
struct dm_mem_cache_client {int dummy; } ;
typedef  enum grow { ____Placeholder_grow } grow ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int SC_GROW ; 
 int /*<<< orphan*/  dm_mem_cache_alloc (struct dm_mem_cache_client*) ; 
 int dm_mem_cache_grow (struct dm_mem_cache_client*,int) ; 
 int /*<<< orphan*/  dm_mem_cache_shrink (struct dm_mem_cache_client*,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stripe*) ; 
 struct stripe* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_init (struct stripe_cache*,struct stripe*) ; 

__attribute__((used)) static struct stripe *stripe_alloc(struct stripe_cache *sc,
				   struct dm_mem_cache_client *mc,
				   enum grow grow)
{
	int r;
	struct stripe *stripe;

	stripe = kmem_cache_zalloc(sc->kc.cache, GFP_KERNEL);
	if (stripe) {
		/* Grow the dm-mem-cache by one object. */
		if (grow == SC_GROW) {
			r = dm_mem_cache_grow(mc, 1);
			if (r)
				goto err_free;
		}

		stripe->obj = dm_mem_cache_alloc(mc);
		if (IS_ERR(stripe->obj))
			goto err_shrink;

		stripe_init(sc, stripe);
	}

	return stripe;

err_shrink:
	if (grow == SC_GROW)
		dm_mem_cache_shrink(mc, 1);
err_free:
	kmem_cache_free(sc->kc.cache, stripe);
	return NULL;
}