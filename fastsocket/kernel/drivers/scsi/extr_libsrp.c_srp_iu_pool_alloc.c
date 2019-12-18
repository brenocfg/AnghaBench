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
struct srp_queue {struct iu_entry* pool; struct iu_entry* items; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;
struct srp_buf {int dummy; } ;
struct iu_entry {struct srp_buf* sbuf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ ,void*,int) ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_init (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iu_entry*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srp_iu_pool_alloc(struct srp_queue *q, size_t max,
			     struct srp_buf **ring)
{
	int i;
	struct iu_entry *iue;

	q->pool = kcalloc(max, sizeof(struct iu_entry *), GFP_KERNEL);
	if (!q->pool)
		return -ENOMEM;
	q->items = kcalloc(max, sizeof(struct iu_entry), GFP_KERNEL);
	if (!q->items)
		goto free_pool;

	spin_lock_init(&q->lock);
	q->queue = kfifo_init((void *) q->pool, max * sizeof(void *),
			      GFP_KERNEL, &q->lock);
	if (IS_ERR(q->queue))
		goto free_item;

	for (i = 0, iue = q->items; i < max; i++) {
		__kfifo_put(q->queue, (void *) &iue, sizeof(void *));
		iue->sbuf = ring[i];
		iue++;
	}
	return 0;

free_item:
	kfree(q->items);
free_pool:
	kfree(q->pool);
	return -ENOMEM;
}