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
struct i2o_pool {int /*<<< orphan*/  name; int /*<<< orphan*/  slab; int /*<<< orphan*/  mempool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int i2o_pool_alloc(struct i2o_pool *pool, const char *name,
				 size_t size, int min_nr)
{
	pool->name = kmalloc(strlen(name) + 1, GFP_KERNEL);
	if (!pool->name)
		goto exit;
	strcpy(pool->name, name);

	pool->slab =
	    kmem_cache_create(pool->name, size, 0, SLAB_HWCACHE_ALIGN, NULL);
	if (!pool->slab)
		goto free_name;

	pool->mempool = mempool_create_slab_pool(min_nr, pool->slab);
	if (!pool->mempool)
		goto free_slab;

	return 0;

free_slab:
	kmem_cache_destroy(pool->slab);

free_name:
	kfree(pool->name);

exit:
	return -ENOMEM;
}