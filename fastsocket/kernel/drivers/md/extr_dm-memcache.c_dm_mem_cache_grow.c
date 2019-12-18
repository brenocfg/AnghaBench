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
 struct page_list* alloc_cache_pages (unsigned int) ; 
 int /*<<< orphan*/  mempool_resize (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int dm_mem_cache_grow(struct dm_mem_cache_client *cl, unsigned objects)
{
	unsigned pages = objects * cl->chunks * cl->pages_per_chunk;
	struct page_list *pl, *last;

	BUG_ON(!pages);
	pl = alloc_cache_pages(pages);
	if (!pl)
		return -ENOMEM;

	last = pl;
	while (last->next)
		last = last->next;

	spin_lock_irq(&cl->lock);
	last->next = cl->free_list;
	cl->free_list = pl;
	cl->free_pages += pages;
	cl->total_pages += pages;
	cl->objects += objects;
	spin_unlock_irq(&cl->lock);

	mempool_resize(cl->objs_pool, cl->objects, GFP_NOIO);
	return 0;
}