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
struct spi_device {TYPE_1__* master; } ;
struct chip_data {int chip_select_num; int /*<<< orphan*/  cs_gpio; } ;
struct TYPE_2__ {int num_chipselect; size_t bus_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 int /*<<< orphan*/  peripheral_free (int /*<<< orphan*/ ) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/ ** ssel ; 

__attribute__((used)) static void bfin_spi_cleanup(struct spi_device *spi)
{
	struct chip_data *chip = spi_get_ctldata(spi);

	if (!chip)
		return;

	if ((chip->chip_select_num > 0)
		&& (chip->chip_select_num <= spi->master->num_chipselect))
		peripheral_free(ssel[spi->master->bus_num]
					[chip->chip_select_num-1]);

	if (chip->chip_select_num == 0)
		gpio_free(chip->cs_gpio);

	kfree(chip);
}