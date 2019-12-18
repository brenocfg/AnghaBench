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
struct tty_struct {int dummy; } ;
struct line {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; struct tty_struct* tty; } ;
struct chan {struct line* line; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int flush_buffer (struct line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static irqreturn_t line_write_interrupt(int irq, void *data)
{
	struct chan *chan = data;
	struct line *line = chan->line;
	struct tty_struct *tty = line->tty;
	int err;

	/*
	 * Interrupts are disabled here because we registered the interrupt with
	 * IRQF_DISABLED (see line_setup_irq).
	 */

	spin_lock(&line->lock);
	err = flush_buffer(line);
	if (err == 0) {
		return IRQ_NONE;
	} else if (err < 0) {
		line->head = line->buffer;
		line->tail = line->buffer;
	}
	spin_unlock(&line->lock);

	if (tty == NULL)
		return IRQ_NONE;

	tty_wakeup(tty);
	return IRQ_HANDLED;
}