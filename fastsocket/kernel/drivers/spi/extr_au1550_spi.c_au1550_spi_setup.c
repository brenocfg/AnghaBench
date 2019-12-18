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
struct spi_device {int bits_per_word; scalar_t__ max_speed_hz; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct au1550_spi {scalar_t__ freq_max; scalar_t__ freq_min; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct au1550_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1550_spi_setup(struct spi_device *spi)
{
	struct au1550_spi *hw = spi_master_get_devdata(spi->master);

	if (spi->bits_per_word < 4 || spi->bits_per_word > 24) {
		dev_err(&spi->dev, "setup: invalid bits_per_word=%d\n",
			spi->bits_per_word);
		return -EINVAL;
	}

	if (spi->max_speed_hz == 0)
		spi->max_speed_hz = hw->freq_max;
	if (spi->max_speed_hz > hw->freq_max
			|| spi->max_speed_hz < hw->freq_min)
		return -EINVAL;
	/*
	 * NOTE: cannot change speed and other hw settings immediately,
	 *       otherwise sharing of spi bus is not possible,
	 *       so do not call setupxfer(spi, NULL) here
	 */
	return 0;
}