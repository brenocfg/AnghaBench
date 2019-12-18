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
struct of_mmc_spi {int* alow_gpios; int /*<<< orphan*/ * gpios; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 struct of_mmc_spi* to_of_mmc_spi (struct device*) ; 

__attribute__((used)) static int of_mmc_spi_read_gpio(struct device *dev, int gpio_num)
{
	struct of_mmc_spi *oms = to_of_mmc_spi(dev);
	bool active_low = oms->alow_gpios[gpio_num];
	bool value = gpio_get_value(oms->gpios[gpio_num]);

	return active_low ^ value;
}