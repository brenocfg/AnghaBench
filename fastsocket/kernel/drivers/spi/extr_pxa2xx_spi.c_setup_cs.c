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
struct spi_device {int mode; int /*<<< orphan*/  dev; } ;
struct pxa2xx_spi_chip {int /*<<< orphan*/  gpio_cs; scalar_t__ cs_control; } ;
struct chip_data {int gpio_cs_inverted; int /*<<< orphan*/  gpio_cs; scalar_t__ cs_control; } ;

/* Variables and functions */
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int setup_cs(struct spi_device *spi, struct chip_data *chip,
		    struct pxa2xx_spi_chip *chip_info)
{
	int err = 0;

	if (chip == NULL || chip_info == NULL)
		return 0;

	/* NOTE: setup() can be called multiple times, possibly with
	 * different chip_info, release previously requested GPIO
	 */
	if (gpio_is_valid(chip->gpio_cs))
		gpio_free(chip->gpio_cs);

	/* If (*cs_control) is provided, ignore GPIO chip select */
	if (chip_info->cs_control) {
		chip->cs_control = chip_info->cs_control;
		return 0;
	}

	if (gpio_is_valid(chip_info->gpio_cs)) {
		err = gpio_request(chip_info->gpio_cs, "SPI_CS");
		if (err) {
			dev_err(&spi->dev, "failed to request chip select "
					"GPIO%d\n", chip_info->gpio_cs);
			return err;
		}

		chip->gpio_cs = chip_info->gpio_cs;
		chip->gpio_cs_inverted = spi->mode & SPI_CS_HIGH;

		err = gpio_direction_output(chip->gpio_cs,
					!chip->gpio_cs_inverted);
	}

	return err;
}