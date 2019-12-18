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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {unsigned int bits_per_word; unsigned int speed_hz; } ;
struct spi_device {unsigned int bits_per_word; unsigned int max_speed_hz; int mode; int /*<<< orphan*/  dev; struct s3c24xx_spi_devstate* controller_state; } ;
struct s3c24xx_spi_devstate {int mode; unsigned int hz; unsigned int sppre; int /*<<< orphan*/  spcon; } ;
struct s3c24xx_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned long,unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  S3C2410_SPCON_CPHA_FMTB ; 
 int /*<<< orphan*/  S3C2410_SPCON_CPOL_HIGH ; 
 int /*<<< orphan*/  SPCON_DEFAULT ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct s3c24xx_spi* to_hw (struct spi_device*) ; 

__attribute__((used)) static int s3c24xx_spi_update_state(struct spi_device *spi,
				    struct spi_transfer *t)
{
	struct s3c24xx_spi *hw = to_hw(spi);
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	unsigned int bpw;
	unsigned int hz;
	unsigned int div;
	unsigned long clk;

	bpw = t ? t->bits_per_word : spi->bits_per_word;
	hz  = t ? t->speed_hz : spi->max_speed_hz;

	if (!bpw)
		bpw = 8;

	if (!hz)
		hz = spi->max_speed_hz;

	if (bpw != 8) {
		dev_err(&spi->dev, "invalid bits-per-word (%d)\n", bpw);
		return -EINVAL;
	}

	if (spi->mode != cs->mode) {
		u8 spcon = SPCON_DEFAULT;

		if (spi->mode & SPI_CPHA)
			spcon |= S3C2410_SPCON_CPHA_FMTB;

		if (spi->mode & SPI_CPOL)
			spcon |= S3C2410_SPCON_CPOL_HIGH;

		cs->mode = spi->mode;
		cs->spcon = spcon;
	}

	if (cs->hz != hz) {
		clk = clk_get_rate(hw->clk);
		div = DIV_ROUND_UP(clk, hz * 2) - 1;

		if (div > 255)
			div = 255;

		dev_dbg(&spi->dev, "pre-scaler=%d (wanted %d, got %ld)\n",
			div, hz, clk / (2 * (div + 1)));

		cs->hz = hz;
		cs->sppre = div;
	}

	return 0;
}