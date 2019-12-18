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
struct page_list {struct page_list* next; } ;
struct dm_mem_cache_client {unsigned int chunks; unsigned int pages_per_chunk; unsigned int free_pages; unsigned int total_pages; unsigned int objects; int /*<<< orphan*/  objs_pool; int /*<<< orphan*/  lock; struct page_list* free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  free_cache_pages (struct page_list*) ; 
 int /*<<< orphan*/  mempool_resize (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dm_mem_cache_shrink(struct dm_mem_cache_client *cl, unsigned objects)
{
	int r;
	unsigned pages = objects * cl->chunks * cl->pages_per_chunk, p = pages;
	unsigned long flags;
	struct page_list *last = NULL, *pl, *pos;

	BUG_ON(!pages);

	spin_lock_irqsave(&cl->lock, flags);
	pl = pos = cl->free_list;
	while (p-- && pos->next) {
		last = pos;
		pos = pos->next;
	}

	if (++p)
		r = -ENOMEM;
	else {
		r = 0;
		cl->free_list = pos;
		cl->free_pages -= pages;
		cl->total_pages -= pages;
		cl->objects -= objects;
		last->next = NULL;
	}
	spin_unlock_irqrestore(&cl->lock, flags);

	if (!r) {
		free_cache_pages(pl);
		mempool_resize(cl->objs_pool, cl->objects, GFP_NOIO);
	}

	return r;
}