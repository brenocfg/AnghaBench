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
struct tty_struct {struct line* driver_data; } ;
struct line {TYPE_1__* driver; int /*<<< orphan*/  chan_list; scalar_t__ throttled; int /*<<< orphan*/  task; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_interrupt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reactivate_chan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void line_unthrottle(struct tty_struct *tty)
{
	struct line *line = tty->driver_data;

	line->throttled = 0;
	chan_interrupt(&line->chan_list, &line->task, tty,
		       line->driver->read_irq);

	/*
	 * Maybe there is enough stuff pending that calling the interrupt
	 * throttles us again.  In this case, line->throttled will be 1
	 * again and we shouldn't turn the interrupt back on.
	 */
	if (!line->throttled)
		reactivate_chan(&line->chan_list, line->driver->read_irq);
}