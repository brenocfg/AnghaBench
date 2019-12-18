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
struct gpio_chip {int base; int /*<<< orphan*/  label; } ;
struct of_gpio_chip {scalar_t__ xlate; struct gpio_chip gc; } ;
struct of_mm_gpio_chip {int /*<<< orphan*/  regs; int /*<<< orphan*/  (* save_regs ) (struct of_mm_gpio_chip*) ;struct of_gpio_chip of_gc; } ;
struct device_node {int /*<<< orphan*/  full_name; struct of_gpio_chip* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gpiochip_add (struct gpio_chip*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_gpio_simple_xlate ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct of_mm_gpio_chip*) ; 

int of_mm_gpiochip_add(struct device_node *np,
		       struct of_mm_gpio_chip *mm_gc)
{
	int ret = -ENOMEM;
	struct of_gpio_chip *of_gc = &mm_gc->of_gc;
	struct gpio_chip *gc = &of_gc->gc;

	gc->label = kstrdup(np->full_name, GFP_KERNEL);
	if (!gc->label)
		goto err0;

	mm_gc->regs = of_iomap(np, 0);
	if (!mm_gc->regs)
		goto err1;

	gc->base = -1;

	if (!of_gc->xlate)
		of_gc->xlate = of_gpio_simple_xlate;

	if (mm_gc->save_regs)
		mm_gc->save_regs(mm_gc);

	np->data = of_gc;

	ret = gpiochip_add(gc);
	if (ret)
		goto err2;

	/* We don't want to lose the node and its ->data */
	of_node_get(np);

	pr_debug("%s: registered as generic GPIO chip, base is %d\n",
		 np->full_name, gc->base);
	return 0;
err2:
	np->data = NULL;
	iounmap(mm_gc->regs);
err1:
	kfree(gc->label);
err0:
	pr_err("%s: GPIO chip registration failed with status %d\n",
	       np->full_name, ret);
	return ret;
}