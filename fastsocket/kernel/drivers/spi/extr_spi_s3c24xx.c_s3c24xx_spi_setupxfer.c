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
struct spi_transfer {int dummy; } ;
struct spi_device {struct s3c24xx_spi_devstate* controller_state; } ;
struct s3c24xx_spi_devstate {int /*<<< orphan*/  sppre; } ;
struct s3c24xx_spi {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2410_SPPRE ; 
 int s3c24xx_spi_update_state (struct spi_device*,struct spi_transfer*) ; 
 struct s3c24xx_spi* to_hw (struct spi_device*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_spi_setupxfer(struct spi_device *spi,
				 struct spi_transfer *t)
{
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	struct s3c24xx_spi *hw = to_hw(spi);
	int ret;

	ret = s3c24xx_spi_update_state(spi, t);
	if (!ret)
		writeb(cs->sppre, hw->regs + S3C2410_SPPRE);

	return ret;
}