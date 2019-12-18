#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int min_nr; int curr_nr; void* pool_data; void* (* alloc ) (int,void*) ;int /*<<< orphan*/ * free; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; void* elements; } ;
typedef  TYPE_1__ mempool_t ;
typedef  int /*<<< orphan*/  mempool_free_t ;
typedef  void* (* mempool_alloc_t ) (int,void*) ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  add_element (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  free_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kmalloc_node (int,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* stub1 (int,void*) ; 
 scalar_t__ unlikely (int) ; 

mempool_t *mempool_create_node(int min_nr, mempool_alloc_t *alloc_fn,
			mempool_free_t *free_fn, void *pool_data, int node_id)
{
	mempool_t *pool;
	pool = kmalloc_node(sizeof(*pool), GFP_KERNEL | __GFP_ZERO, node_id);
	if (!pool)
		return NULL;
	pool->elements = kmalloc_node(min_nr * sizeof(void *),
					GFP_KERNEL, node_id);
	if (!pool->elements) {
		kfree(pool);
		return NULL;
	}
	spin_lock_init(&pool->lock);
	pool->min_nr = min_nr;
	pool->pool_data = pool_data;
	init_waitqueue_head(&pool->wait);
	pool->alloc = alloc_fn;
	pool->free = free_fn;

	/*
	 * First pre-allocate the guaranteed number of buffers.
	 */
	while (pool->curr_nr < pool->min_nr) {
		void *element;

		element = pool->alloc(GFP_KERNEL, pool->pool_data);
		if (unlikely(!element)) {
			free_pool(pool);
			return NULL;
		}
		add_element(pool, element);
	}
	return pool;
}