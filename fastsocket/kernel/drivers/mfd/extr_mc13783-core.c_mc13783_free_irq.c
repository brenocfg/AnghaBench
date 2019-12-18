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
struct mc13783 {int /*<<< orphan*/  io_lock; TYPE_1__* irq_handler; } ;
struct TYPE_2__ {int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int EINVAL ; 
 int MC13783_NUM_IRQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mc13783_free_irq(struct mc13783 *mc13783, int irq)
{
	if (irq < 0 || irq > MC13783_NUM_IRQ)
		return -EINVAL;

	mutex_lock(&mc13783->io_lock);
	mc13783->irq_handler[irq].handler = NULL;
	mutex_unlock(&mc13783->io_lock);

	return 0;
}