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
struct ad7877 {int pending; int /*<<< orphan*/  lock; TYPE_1__* spi; int /*<<< orphan*/  msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_async (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ad7877_irq(int irq, void *handle)
{
	struct ad7877 *ts = handle;
	unsigned long flags;
	int status;

	/*
	 * The repeated conversion sequencer controlled by TMR kicked off
	 * too fast. We ignore the last and process the sample sequence
	 * currently in the queue. It can't be older than 9.4ms, and we
	 * need to avoid that ts->msg doesn't get issued twice while in work.
	 */

	spin_lock_irqsave(&ts->lock, flags);
	if (!ts->pending) {
		ts->pending = 1;

		status = spi_async(ts->spi, &ts->msg);
		if (status)
			dev_err(&ts->spi->dev, "spi_sync --> %d\n", status);
	}
	spin_unlock_irqrestore(&ts->lock, flags);

	return IRQ_HANDLED;
}