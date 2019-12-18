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
struct gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  _clear_gpio_irqstatus (struct gpio_bank*,int) ; 
 int /*<<< orphan*/  _set_gpio_direction (struct gpio_bank*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _set_gpio_irqenable (struct gpio_bank*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_gpio_triggering (struct gpio_bank*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_gpio_index (int) ; 

__attribute__((used)) static void _reset_gpio(struct gpio_bank *bank, int gpio)
{
	_set_gpio_direction(bank, get_gpio_index(gpio), 1);
	_set_gpio_irqenable(bank, gpio, 0);
	_clear_gpio_irqstatus(bank, gpio);
	_set_gpio_triggering(bank, get_gpio_index(gpio), IRQ_TYPE_NONE);
}