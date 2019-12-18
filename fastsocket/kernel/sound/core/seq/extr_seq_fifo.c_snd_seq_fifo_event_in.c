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
struct snd_seq_fifo {int /*<<< orphan*/  use_lock; int /*<<< orphan*/  input_sleep; int /*<<< orphan*/  lock; int /*<<< orphan*/  cells; struct snd_seq_event_cell* head; struct snd_seq_event_cell* tail; int /*<<< orphan*/  overflow; int /*<<< orphan*/  pool; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; } ;
struct snd_seq_event {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_seq_event_dup (int /*<<< orphan*/ ,struct snd_seq_event*,struct snd_seq_event_cell**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_use_lock_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int snd_seq_fifo_event_in(struct snd_seq_fifo *f,
			  struct snd_seq_event *event)
{
	struct snd_seq_event_cell *cell;
	unsigned long flags;
	int err;

	if (snd_BUG_ON(!f))
		return -EINVAL;

	snd_use_lock_use(&f->use_lock);
	err = snd_seq_event_dup(f->pool, event, &cell, 1, NULL); /* always non-blocking */
	if (err < 0) {
		if (err == -ENOMEM)
			atomic_inc(&f->overflow);
		snd_use_lock_free(&f->use_lock);
		return err;
	}
		
	/* append new cells to fifo */
	spin_lock_irqsave(&f->lock, flags);
	if (f->tail != NULL)
		f->tail->next = cell;
	f->tail = cell;
	if (f->head == NULL)
		f->head = cell;
	f->cells++;
	spin_unlock_irqrestore(&f->lock, flags);

	/* wakeup client */
	if (waitqueue_active(&f->input_sleep))
		wake_up(&f->input_sleep);

	snd_use_lock_free(&f->use_lock);

	return 0; /* success */

}