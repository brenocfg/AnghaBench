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
struct snd_seq_pool {int dummy; } ;
struct snd_seq_fifo {int /*<<< orphan*/  lock; scalar_t__ cells; int /*<<< orphan*/ * tail; struct snd_seq_event_cell* head; struct snd_seq_pool* pool; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_seq_cell_free (struct snd_seq_event_cell*) ; 
 int /*<<< orphan*/  snd_seq_pool_delete (struct snd_seq_pool**) ; 
 scalar_t__ snd_seq_pool_init (struct snd_seq_pool*) ; 
 struct snd_seq_pool* snd_seq_pool_new (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_seq_fifo_resize(struct snd_seq_fifo *f, int poolsize)
{
	unsigned long flags;
	struct snd_seq_pool *newpool, *oldpool;
	struct snd_seq_event_cell *cell, *next, *oldhead;

	if (snd_BUG_ON(!f || !f->pool))
		return -EINVAL;

	/* allocate new pool */
	newpool = snd_seq_pool_new(poolsize);
	if (newpool == NULL)
		return -ENOMEM;
	if (snd_seq_pool_init(newpool) < 0) {
		snd_seq_pool_delete(&newpool);
		return -ENOMEM;
	}

	spin_lock_irqsave(&f->lock, flags);
	/* remember old pool */
	oldpool = f->pool;
	oldhead = f->head;
	/* exchange pools */
	f->pool = newpool;
	f->head = NULL;
	f->tail = NULL;
	f->cells = 0;
	/* NOTE: overflow flag is not cleared */
	spin_unlock_irqrestore(&f->lock, flags);

	/* release cells in old pool */
	for (cell = oldhead; cell; cell = next) {
		next = cell->next;
		snd_seq_cell_free(cell);
	}
	snd_seq_pool_delete(&oldpool);

	return 0;
}