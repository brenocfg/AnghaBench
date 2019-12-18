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
struct wm831x {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * handler_data; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 unsigned int WM831X_NUM_IRQS ; 
 int /*<<< orphan*/  __wm831x_disable_irq (struct wm831x*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wm831x_irqs ; 

void wm831x_free_irq(struct wm831x *wm831x, unsigned int irq, void *data)
{
	if (irq < 0 || irq >= WM831X_NUM_IRQS)
		return;

	mutex_lock(&wm831x->irq_lock);

	wm831x_irqs[irq].handler = NULL;
	wm831x_irqs[irq].handler_data = NULL;

	__wm831x_disable_irq(wm831x, irq);

	mutex_unlock(&wm831x->irq_lock);
}