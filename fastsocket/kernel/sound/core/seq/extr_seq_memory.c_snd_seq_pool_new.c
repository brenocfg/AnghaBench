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
struct snd_seq_pool {int size; scalar_t__ max_used; int /*<<< orphan*/  output_sleep; scalar_t__ closing; int /*<<< orphan*/  counter; scalar_t__ total_elements; int /*<<< orphan*/ * free; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct snd_seq_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct snd_seq_pool *snd_seq_pool_new(int poolsize)
{
	struct snd_seq_pool *pool;

	/* create pool block */
	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (pool == NULL) {
		snd_printd("seq: malloc failed for pool\n");
		return NULL;
	}
	spin_lock_init(&pool->lock);
	pool->ptr = NULL;
	pool->free = NULL;
	pool->total_elements = 0;
	atomic_set(&pool->counter, 0);
	pool->closing = 0;
	init_waitqueue_head(&pool->output_sleep);
	
	pool->size = poolsize;

	/* init statistics */
	pool->max_used = 0;
	return pool;
}