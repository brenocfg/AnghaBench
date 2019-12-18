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
struct gpio_chip {int can_sleep; int base; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  set; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; } ;
struct of_gpio_chip {int gpio_cells; int /*<<< orphan*/  xlate; struct gpio_chip gc; } ;
struct mcu {struct device_node* np; struct of_gpio_chip of_gc; } ;
struct device_node {struct of_gpio_chip* data; int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MCU_NUM_GPIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int gpiochip_add (struct gpio_chip*) ; 
 int /*<<< orphan*/  mcu_gpio_dir_out ; 
 int /*<<< orphan*/  mcu_gpio_set ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_gpio_simple_xlate ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int mcu_gpiochip_add(struct mcu *mcu)
{
	struct device_node *np;
	struct of_gpio_chip *of_gc = &mcu->of_gc;
	struct gpio_chip *gc = &of_gc->gc;
	int ret;

	np = of_find_compatible_node(NULL, NULL, "fsl,mcu-mpc8349emitx");
	if (!np)
		return -ENODEV;

	gc->owner = THIS_MODULE;
	gc->label = np->full_name;
	gc->can_sleep = 1;
	gc->ngpio = MCU_NUM_GPIO;
	gc->base = -1;
	gc->set = mcu_gpio_set;
	gc->direction_output = mcu_gpio_dir_out;
	of_gc->gpio_cells = 2;
	of_gc->xlate = of_gpio_simple_xlate;

	np->data = of_gc;
	mcu->np = np;

	/*
	 * We don't want to lose the node, its ->data and ->full_name...
	 * So, if succeeded, we don't put the node here.
	 */
	ret = gpiochip_add(gc);
	if (ret)
		of_node_put(np);
	return ret;
}