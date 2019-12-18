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
struct led_classdev {struct gpio_trig_data* trigger_data; } ;
struct gpio_trig_data {int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t gpio_trig_irq(int irq, void *_led)
{
	struct led_classdev *led = _led;
	struct gpio_trig_data *gpio_data = led->trigger_data;

	/* just schedule_work since gpio_get_value can sleep */
	schedule_work(&gpio_data->work);

	return IRQ_HANDLED;
}