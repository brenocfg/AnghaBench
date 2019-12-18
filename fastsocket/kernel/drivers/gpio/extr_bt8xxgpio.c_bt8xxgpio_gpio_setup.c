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
struct gpio_chip {scalar_t__ can_sleep; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; int /*<<< orphan*/ * dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct bt8xxgpio {TYPE_1__* pdev; struct gpio_chip gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT8XXGPIO_NR_GPIOS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bt8xxgpio_gpio_direction_input ; 
 int /*<<< orphan*/  bt8xxgpio_gpio_direction_output ; 
 int /*<<< orphan*/  bt8xxgpio_gpio_get ; 
 int /*<<< orphan*/  bt8xxgpio_gpio_set ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modparam_gpiobase ; 

__attribute__((used)) static void bt8xxgpio_gpio_setup(struct bt8xxgpio *bg)
{
	struct gpio_chip *c = &bg->gpio;

	c->label = dev_name(&bg->pdev->dev);
	c->owner = THIS_MODULE;
	c->direction_input = bt8xxgpio_gpio_direction_input;
	c->get = bt8xxgpio_gpio_get;
	c->direction_output = bt8xxgpio_gpio_direction_output;
	c->set = bt8xxgpio_gpio_set;
	c->dbg_show = NULL;
	c->base = modparam_gpiobase;
	c->ngpio = BT8XXGPIO_NR_GPIOS;
	c->can_sleep = 0;
}