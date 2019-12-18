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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOSA_GPIO_L_MUTE ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tosa_probe(struct platform_device *dev)
{
	int ret;

	ret = gpio_request(TOSA_GPIO_L_MUTE, "Headphone Jack");
	if (ret)
		return ret;
	ret = gpio_direction_output(TOSA_GPIO_L_MUTE, 0);
	if (ret)
		gpio_free(TOSA_GPIO_L_MUTE);

	return ret;
}