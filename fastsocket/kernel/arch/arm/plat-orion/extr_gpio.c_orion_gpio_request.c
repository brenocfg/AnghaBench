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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INPUT_OK ; 
 int /*<<< orphan*/  GPIO_OUTPUT_OK ; 
 scalar_t__ orion_gpio_is_valid (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orion_gpio_request(struct gpio_chip *chip, unsigned pin)
{
	if (orion_gpio_is_valid(pin, GPIO_INPUT_OK) ||
	    orion_gpio_is_valid(pin, GPIO_OUTPUT_OK))
		return 0;
	return -EINVAL;
}