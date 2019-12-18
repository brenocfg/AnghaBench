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
struct device {int /*<<< orphan*/ * platform_data; int /*<<< orphan*/  archdata; } ;
struct spi_device {struct device dev; } ;
struct of_mmc_spi {int /*<<< orphan*/ * gpios; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct device_node* dev_archdata_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct of_mmc_spi*) ; 
 struct of_mmc_spi* to_of_mmc_spi (struct device*) ; 

void mmc_spi_put_pdata(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct device_node *np = dev_archdata_get_node(&dev->archdata);
	struct of_mmc_spi *oms = to_of_mmc_spi(dev);
	int i;

	if (!dev->platform_data || !np)
		return;

	for (i = 0; i < ARRAY_SIZE(oms->gpios); i++) {
		if (gpio_is_valid(oms->gpios[i]))
			gpio_free(oms->gpios[i]);
	}
	kfree(oms);
	dev->platform_data = NULL;
}