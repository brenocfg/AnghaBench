#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {char* label; int ngpio; int base; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  owner; } ;
struct bcma_drv_cc {TYPE_2__* core; struct gpio_chip gpio; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {scalar_t__ hosttype; } ;

/* Variables and functions */
 scalar_t__ BCMA_HOSTTYPE_SOC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bcma_gpio_direction_input ; 
 int /*<<< orphan*/  bcma_gpio_direction_output ; 
 int /*<<< orphan*/  bcma_gpio_free ; 
 int /*<<< orphan*/  bcma_gpio_get_value ; 
 int /*<<< orphan*/  bcma_gpio_request ; 
 int /*<<< orphan*/  bcma_gpio_set_value ; 
 int gpiochip_add (struct gpio_chip*) ; 

int bcma_gpio_init(struct bcma_drv_cc *cc)
{
	struct gpio_chip *chip = &cc->gpio;

	chip->label		= "bcma_gpio";
	chip->owner		= THIS_MODULE;
	chip->request		= bcma_gpio_request;
	chip->free		= bcma_gpio_free;
	chip->get		= bcma_gpio_get_value;
	chip->set		= bcma_gpio_set_value;
	chip->direction_input	= bcma_gpio_direction_input;
	chip->direction_output	= bcma_gpio_direction_output;
	chip->ngpio		= 16;
	/* There is just one SoC in one device and its GPIO addresses should be
	 * deterministic to address them more easily. The other buses could get
	 * a random base number. */
	if (cc->core->bus->hosttype == BCMA_HOSTTYPE_SOC)
		chip->base		= 0;
	else
		chip->base		= -1;

	return gpiochip_add(chip);
}