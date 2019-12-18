#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_page_pool {scalar_t__ npages; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct page {int /*<<< orphan*/  lru; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_3__ {scalar_t__ max_size; } ;
struct TYPE_4__ {TYPE_1__ options; } ;

/* Variables and functions */
 unsigned int NUM_PAGES_TO_ALLOC ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 TYPE_2__* _manager ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ttm_page_pool* ttm_get_pool (int,int) ; 
 int /*<<< orphan*/  ttm_page_pool_free (struct ttm_page_pool*,unsigned int) ; 

__attribute__((used)) static void ttm_put_pages(struct page **pages, unsigned npages, int flags,
			  enum ttm_caching_state cstate)
{
	unsigned long irq_flags;
	struct ttm_page_pool *pool = ttm_get_pool(flags, cstate);
	unsigned i;

	if (pool == NULL) {
		/* No pool for this memory type so free the pages */
		for (i = 0; i < npages; i++) {
			if (pages[i]) {
				if (page_count(pages[i]) != 1)
					pr_err("Erroneous page count. Leaking pages.\n");
				__free_page(pages[i]);
				pages[i] = NULL;
			}
		}
		return;
	}

	spin_lock_irqsave(&pool->lock, irq_flags);
	for (i = 0; i < npages; i++) {
		if (pages[i]) {
			if (page_count(pages[i]) != 1)
				pr_err("Erroneous page count. Leaking pages.\n");
			list_add_tail(&pages[i]->lru, &pool->list);
			pages[i] = NULL;
			pool->npages++;
		}
	}
	/* Check that we don't go over the pool limit */
	npages = 0;
	if (pool->npages > _manager->options.max_size) {
		npages = pool->npages - _manager->options.max_size;
		/* free at least NUM_PAGES_TO_ALLOC number of pages
		 * to reduce calls to set_memory_wb */
		if (npages < NUM_PAGES_TO_ALLOC)
			npages = NUM_PAGES_TO_ALLOC;
	}
	spin_unlock_irqrestore(&pool->lock, irq_flags);
	if (npages)
		ttm_page_pool_free(pool, npages);
}