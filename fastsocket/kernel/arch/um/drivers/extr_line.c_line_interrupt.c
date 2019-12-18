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
struct line {int /*<<< orphan*/  task; int /*<<< orphan*/  chan_list; struct tty_struct* tty; } ;
struct chan {struct line* line; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  chan_interrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tty_struct*,int) ; 

__attribute__((used)) static irqreturn_t line_interrupt(int irq, void *data)
{
	struct chan *chan = data;
	struct line *line = chan->line;
	struct tty_struct *tty = line->tty;

	if (line)
		chan_interrupt(&line->chan_list, &line->task, tty, irq);
	return IRQ_HANDLED;
}