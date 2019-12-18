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
struct wm831x {int /*<<< orphan*/  irq_work; int /*<<< orphan*/  irq_wq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t wm831x_cpu_irq(int irq, void *data)
{
	struct wm831x *wm831x = data;

	/* Shut the interrupt to the CPU up and schedule the actual
	 * handler; we can't check that the IRQ is asserted. */
	disable_irq_nosync(irq);

	queue_work(wm831x->irq_wq, &wm831x->irq_work);

	return IRQ_HANDLED;
}