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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bat_work ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_gpio (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tosa_bat_gpio_isr(int irq, void *data)
{
	pr_info("tosa_bat_gpio irq: %d\n", gpio_get_value(irq_to_gpio(irq)));
	schedule_work(&bat_work);
	return IRQ_HANDLED;
}