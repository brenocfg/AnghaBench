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
struct wm831x_irq_data {int /*<<< orphan*/  mask; int /*<<< orphan*/  handler_data; int /*<<< orphan*/  (* handler ) (int,int /*<<< orphan*/ ) ;} ;
struct wm831x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wm831x_disable_irq (struct wm831x*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  irq_data_to_status_reg (struct wm831x_irq_data*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 struct wm831x_irq_data* wm831x_irqs ; 
 int /*<<< orphan*/  wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm831x_handle_irq(struct wm831x *wm831x, int irq, int status)
{
	struct wm831x_irq_data *irq_data = &wm831x_irqs[irq];

	if (irq_data->handler) {
		irq_data->handler(irq, irq_data->handler_data);
		wm831x_reg_write(wm831x, irq_data_to_status_reg(irq_data),
				 irq_data->mask);
	} else {
		dev_err(wm831x->dev, "Unhandled IRQ %d, masking\n", irq);
		__wm831x_disable_irq(wm831x, irq);
	}
}