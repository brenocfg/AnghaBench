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
struct snd_seq_fifo {int /*<<< orphan*/  lock; int /*<<< orphan*/  cells; struct snd_seq_event_cell* head; } ;
struct snd_seq_event_cell {struct snd_seq_event_cell* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_fifo_cell_putback(struct snd_seq_fifo *f,
			       struct snd_seq_event_cell *cell)
{
	unsigned long flags;

	if (cell) {
		spin_lock_irqsave(&f->lock, flags);
		cell->next = f->head;
		f->head = cell;
		f->cells++;
		spin_unlock_irqrestore(&f->lock, flags);
	}
}