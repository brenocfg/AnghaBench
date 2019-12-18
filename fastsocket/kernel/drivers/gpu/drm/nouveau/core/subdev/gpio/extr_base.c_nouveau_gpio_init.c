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
struct nouveau_gpio {int /*<<< orphan*/  (* reset ) (struct nouveau_gpio*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_reset_ids ; 
 int nouveau_subdev_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_gpio*,int /*<<< orphan*/ ) ; 

int
nouveau_gpio_init(struct nouveau_gpio *gpio)
{
	int ret = nouveau_subdev_init(&gpio->base);
	if (ret == 0 && gpio->reset) {
		if (dmi_check_system(gpio_reset_ids))
			gpio->reset(gpio, DCB_GPIO_UNUSED);
	}
	return ret;
}