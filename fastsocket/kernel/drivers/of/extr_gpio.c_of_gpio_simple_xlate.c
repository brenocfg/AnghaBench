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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ const ngpio; } ;
struct of_gpio_chip {int gpio_cells; TYPE_1__ gc; } ;
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

int of_gpio_simple_xlate(struct of_gpio_chip *of_gc, struct device_node *np,
			 const void *gpio_spec, enum of_gpio_flags *flags)
{
	const u32 *gpio = gpio_spec;

	/*
	 * We're discouraging gpio_cells < 2, since that way you'll have to
	 * write your own xlate function (that will have to retrive the GPIO
	 * number and the flags from a single gpio cell -- this is possible,
	 * but not recommended).
	 */
	if (of_gc->gpio_cells < 2) {
		WARN_ON(1);
		return -EINVAL;
	}

	if (*gpio > of_gc->gc.ngpio)
		return -EINVAL;

	if (flags)
		*flags = gpio[1];

	return *gpio;
}