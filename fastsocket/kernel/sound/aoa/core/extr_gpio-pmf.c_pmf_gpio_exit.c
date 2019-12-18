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
struct TYPE_6__ {scalar_t__ gpio_private; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_5__ {scalar_t__ gpio_private; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_4__ {scalar_t__ gpio_private; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct gpio_runtime {TYPE_3__ line_out_notify; TYPE_2__ line_in_notify; TYPE_1__ headphone_notify; scalar_t__ implementation_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_gpio_all_amps_off (struct gpio_runtime*) ; 
 int /*<<< orphan*/  pmf_unregister_irq_client (scalar_t__) ; 

__attribute__((used)) static void pmf_gpio_exit(struct gpio_runtime *rt)
{
	pmf_gpio_all_amps_off(rt);
	rt->implementation_private = 0;

	if (rt->headphone_notify.gpio_private)
		pmf_unregister_irq_client(rt->headphone_notify.gpio_private);
	if (rt->line_in_notify.gpio_private)
		pmf_unregister_irq_client(rt->line_in_notify.gpio_private);
	if (rt->line_out_notify.gpio_private)
		pmf_unregister_irq_client(rt->line_out_notify.gpio_private);

	/* make sure no work is pending before freeing
	 * all things */
	cancel_delayed_work(&rt->headphone_notify.work);
	cancel_delayed_work(&rt->line_in_notify.work);
	cancel_delayed_work(&rt->line_out_notify.work);
	flush_scheduled_work();

	mutex_destroy(&rt->headphone_notify.mutex);
	mutex_destroy(&rt->line_in_notify.mutex);
	mutex_destroy(&rt->line_out_notify.mutex);

	if (rt->headphone_notify.gpio_private)
		kfree(rt->headphone_notify.gpio_private);
	if (rt->line_in_notify.gpio_private)
		kfree(rt->line_in_notify.gpio_private);
	if (rt->line_out_notify.gpio_private)
		kfree(rt->line_out_notify.gpio_private);
}