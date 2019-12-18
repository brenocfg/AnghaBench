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
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; scalar_t__ gpio_private; scalar_t__ notify; } ;
struct gpio_runtime {TYPE_1__ line_out_notify; TYPE_1__ line_in_notify; TYPE_1__ headphone_notify; scalar_t__ implementation_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ftr_gpio_all_amps_off (struct gpio_runtime*) ; 
 int /*<<< orphan*/  headphone_detect_irq ; 
 int /*<<< orphan*/  linein_detect_irq ; 
 int /*<<< orphan*/  lineout_detect_irq ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftr_gpio_exit(struct gpio_runtime *rt)
{
	ftr_gpio_all_amps_off(rt);
	rt->implementation_private = 0;
	if (rt->headphone_notify.notify)
		free_irq(headphone_detect_irq, &rt->headphone_notify);
	if (rt->line_in_notify.gpio_private)
		free_irq(linein_detect_irq, &rt->line_in_notify);
	if (rt->line_out_notify.gpio_private)
		free_irq(lineout_detect_irq, &rt->line_out_notify);
	cancel_delayed_work(&rt->headphone_notify.work);
	cancel_delayed_work(&rt->line_in_notify.work);
	cancel_delayed_work(&rt->line_out_notify.work);
	flush_scheduled_work();
	mutex_destroy(&rt->headphone_notify.mutex);
	mutex_destroy(&rt->line_in_notify.mutex);
	mutex_destroy(&rt->line_out_notify.mutex);
}