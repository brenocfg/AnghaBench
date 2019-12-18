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
struct dm_mem_cache_object {int dummy; } ;
struct dm_mem_cache_client {unsigned int chunks; unsigned int pages_per_chunk; unsigned int free_pages; int /*<<< orphan*/  objs_pool; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dm_mem_cache_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  alloc_chunks (struct dm_mem_cache_client*,struct dm_mem_cache_object*) ; 
 struct dm_mem_cache_object* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct dm_mem_cache_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct dm_mem_cache_object *dm_mem_cache_alloc(struct dm_mem_cache_client *cl)
{
	int r = 0;
	unsigned pages = cl->chunks * cl->pages_per_chunk;
	unsigned long flags;
	struct dm_mem_cache_object *obj;

	obj = mempool_alloc(cl->objs_pool, GFP_NOIO);
	if (!obj)
		return ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&cl->lock, flags);
	if (pages > cl->free_pages)
		r = -ENOMEM;
	else
		cl->free_pages -= pages;
	spin_unlock_irqrestore(&cl->lock, flags);

	if (r) {
		mempool_free(obj, cl->objs_pool);
		return ERR_PTR(r);
	}

	alloc_chunks(cl, obj);
	return obj;
}