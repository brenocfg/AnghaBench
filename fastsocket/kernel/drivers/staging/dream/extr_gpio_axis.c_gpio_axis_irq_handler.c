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
struct gpio_axis_state {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gpio_event_update_axis (struct gpio_axis_state*,int) ; 

__attribute__((used)) static irqreturn_t gpio_axis_irq_handler(int irq, void *dev_id)
{
	struct gpio_axis_state *as = dev_id;
	gpio_event_update_axis(as, 1);
	return IRQ_HANDLED;
}