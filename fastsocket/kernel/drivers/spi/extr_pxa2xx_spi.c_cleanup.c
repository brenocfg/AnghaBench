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
struct spi_device {int dummy; } ;
struct chip_data {int /*<<< orphan*/  gpio_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 

__attribute__((used)) static void cleanup(struct spi_device *spi)
{
	struct chip_data *chip = spi_get_ctldata(spi);

	if (!chip)
		return;

	if (gpio_is_valid(chip->gpio_cs))
		gpio_free(chip->gpio_cs);

	kfree(chip);
}