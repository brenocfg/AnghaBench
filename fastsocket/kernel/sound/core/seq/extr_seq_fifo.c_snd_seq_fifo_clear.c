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
struct snd_seq_fifo {int /*<<< orphan*/  lock; int /*<<< orphan*/  use_lock; int /*<<< orphan*/  overflow; } ;
struct snd_seq_event_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_seq_event_cell* fifo_cell_out (struct snd_seq_fifo*) ; 
 int /*<<< orphan*/  snd_seq_cell_free (struct snd_seq_event_cell*) ; 
 int /*<<< orphan*/  snd_use_lock_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_fifo_clear(struct snd_seq_fifo *f)
{
	struct snd_seq_event_cell *cell;
	unsigned long flags;

	/* clear overflow flag */
	atomic_set(&f->overflow, 0);

	snd_use_lock_sync(&f->use_lock);
	spin_lock_irqsave(&f->lock, flags);
	/* drain the fifo */
	while ((cell = fifo_cell_out(f)) != NULL) {
		snd_seq_cell_free(cell);
	}
	spin_unlock_irqrestore(&f->lock, flags);
}