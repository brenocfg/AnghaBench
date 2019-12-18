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
struct TYPE_2__ {int max_pages; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  max_maps; } ;
struct rds_ib_mr_pool {int max_free_pinned; int max_items_soft; int max_items; TYPE_1__ fmr_attr; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  flush_wait; int /*<<< orphan*/  flush_lock; int /*<<< orphan*/  clean_list; int /*<<< orphan*/  drop_list; int /*<<< orphan*/  free_list; } ;
struct rds_ib_device {int max_fmrs; int /*<<< orphan*/  fmr_max_remaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rds_ib_mr_pool* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int fmr_message_size ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct rds_ib_mr_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_mr_pool_flush_worker ; 

struct rds_ib_mr_pool *rds_ib_create_mr_pool(struct rds_ib_device *rds_ibdev)
{
	struct rds_ib_mr_pool *pool;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return ERR_PTR(-ENOMEM);

	init_llist_head(&pool->free_list);
	init_llist_head(&pool->drop_list);
	init_llist_head(&pool->clean_list);
	mutex_init(&pool->flush_lock);
	init_waitqueue_head(&pool->flush_wait);
	INIT_DELAYED_WORK(&pool->flush_worker, rds_ib_mr_pool_flush_worker);

	pool->fmr_attr.max_pages = fmr_message_size;
	pool->fmr_attr.max_maps = rds_ibdev->fmr_max_remaps;
	pool->fmr_attr.page_shift = PAGE_SHIFT;
	pool->max_free_pinned = rds_ibdev->max_fmrs * fmr_message_size / 4;

	/* We never allow more than max_items MRs to be allocated.
	 * When we exceed more than max_items_soft, we start freeing
	 * items more aggressively.
	 * Make sure that max_items > max_items_soft > max_items / 2
	 */
	pool->max_items_soft = rds_ibdev->max_fmrs * 3 / 4;
	pool->max_items = rds_ibdev->max_fmrs;

	return pool;
}