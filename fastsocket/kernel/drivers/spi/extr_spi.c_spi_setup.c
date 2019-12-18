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
struct spi_device {unsigned int mode; int bits_per_word; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  dev; TYPE_1__* master; } ;
struct TYPE_2__ {unsigned int mode_bits; int (* setup ) (struct spi_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_3WIRE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LOOP ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int stub1 (struct spi_device*) ; 

int spi_setup(struct spi_device *spi)
{
	unsigned	bad_bits;
	int		status;

	/* help drivers fail *cleanly* when they need options
	 * that aren't supported with their current master
	 */
	bad_bits = spi->mode & ~spi->master->mode_bits;
	if (bad_bits) {
		dev_dbg(&spi->dev, "setup: unsupported mode bits %x\n",
			bad_bits);
		return -EINVAL;
	}

	if (!spi->bits_per_word)
		spi->bits_per_word = 8;

	status = spi->master->setup(spi);

	dev_dbg(&spi->dev, "setup mode %d, %s%s%s%s"
				"%u bits/w, %u Hz max --> %d\n",
			(int) (spi->mode & (SPI_CPOL | SPI_CPHA)),
			(spi->mode & SPI_CS_HIGH) ? "cs_high, " : "",
			(spi->mode & SPI_LSB_FIRST) ? "lsb, " : "",
			(spi->mode & SPI_3WIRE) ? "3wire, " : "",
			(spi->mode & SPI_LOOP) ? "loopback, " : "",
			spi->bits_per_word, spi->max_speed_hz,
			status);

	return status;
}