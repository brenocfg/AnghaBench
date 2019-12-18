#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct chan {int fd; scalar_t__ opened; int /*<<< orphan*/  data; TYPE_3__* ops; scalar_t__ enabled; TYPE_2__* line; scalar_t__ output; scalar_t__ input; int /*<<< orphan*/  free_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  write_irq; int /*<<< orphan*/  read_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct chan*) ; 
 int /*<<< orphan*/  irqs_to_free ; 
 int /*<<< orphan*/  irqs_to_free_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_one_chan(struct chan *chan, int delay_free_irq)
{
	unsigned long flags;

	if (!chan->opened)
		return;

	if (delay_free_irq) {
		spin_lock_irqsave(&irqs_to_free_lock, flags);
		list_add(&chan->free_list, &irqs_to_free);
		spin_unlock_irqrestore(&irqs_to_free_lock, flags);
	}
	else {
		if (chan->input)
			free_irq(chan->line->driver->read_irq, chan);
		if (chan->output)
			free_irq(chan->line->driver->write_irq, chan);
		chan->enabled = 0;
	}
	if (chan->ops->close != NULL)
		(*chan->ops->close)(chan->fd, chan->data);

	chan->opened = 0;
	chan->fd = -1;
}