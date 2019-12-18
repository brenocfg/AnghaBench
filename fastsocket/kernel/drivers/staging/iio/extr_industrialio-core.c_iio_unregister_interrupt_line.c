#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {TYPE_1__** interrupts; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void iio_unregister_interrupt_line(struct iio_dev *dev_info, int line_number)
{
	/* make sure the interrupt handlers are all done */
	flush_scheduled_work();
	free_irq(dev_info->interrupts[line_number]->irq,
		 dev_info->interrupts[line_number]);
	kfree(dev_info->interrupts[line_number]);
}