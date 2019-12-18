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
struct ttm_page_pool {int fill_lock; int gfp_flags; char* name; scalar_t__ nfrees; scalar_t__ npages; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttm_page_pool_init_locked(struct ttm_page_pool *pool, int flags,
		char *name)
{
	spin_lock_init(&pool->lock);
	pool->fill_lock = false;
	INIT_LIST_HEAD(&pool->list);
	pool->npages = pool->nfrees = 0;
	pool->gfp_flags = flags;
	pool->name = name;
}