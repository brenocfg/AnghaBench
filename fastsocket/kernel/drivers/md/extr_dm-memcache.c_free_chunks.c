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
struct dm_mem_cache_object {struct page_list* pl; } ;
struct dm_mem_cache_client {unsigned int chunks; int /*<<< orphan*/  lock; int /*<<< orphan*/  free_pages; struct page_list* free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_chunks(struct dm_mem_cache_client *cl,
			struct dm_mem_cache_object *obj)
{
	unsigned chunks = cl->chunks;
	unsigned long flags;
	struct page_list *next, *pl;

	local_irq_save(flags);
	local_irq_disable();
	while (chunks--) {
		for (pl = obj[chunks].pl; pl; pl = next) {
			next = pl->next;

			spin_lock(&cl->lock);
			pl->next = cl->free_list;
			cl->free_list = pl;
			cl->free_pages++;
			spin_unlock(&cl->lock);
		}
	}

	local_irq_restore(flags);
}