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
typedef  int u32 ;
struct spi_device {unsigned int mode; int chip_select; int /*<<< orphan*/  dev; TYPE_1__* master; struct atmel_spi_device* controller_state; } ;
struct atmel_spi_device {int csr; int /*<<< orphan*/  npcs_pin; } ;
struct atmel_spi {int dummy; } ;
struct TYPE_2__ {int num_chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPOL ; 
 scalar_t__ CSR0 ; 
 int /*<<< orphan*/  MODFDIS ; 
 scalar_t__ MR ; 
 int /*<<< orphan*/  MSTR ; 
 int /*<<< orphan*/  PCS ; 
 int SPI_BF (int /*<<< orphan*/ ,int) ; 
 int SPI_BFINS (int /*<<< orphan*/ ,int,int) ; 
 int SPI_BIT (int /*<<< orphan*/ ) ; 
 int SPI_CPOL ; 
 unsigned int SPI_CS_HIGH ; 
 scalar_t__ atmel_spi_is_v2 () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,unsigned int) ; 
 int spi_readl (struct atmel_spi*,scalar_t__) ; 
 int /*<<< orphan*/  spi_writel (struct atmel_spi*,scalar_t__,int) ; 

__attribute__((used)) static void cs_activate(struct atmel_spi *as, struct spi_device *spi)
{
	struct atmel_spi_device *asd = spi->controller_state;
	unsigned active = spi->mode & SPI_CS_HIGH;
	u32 mr;

	if (atmel_spi_is_v2()) {
		/*
		 * Always use CSR0. This ensures that the clock
		 * switches to the correct idle polarity before we
		 * toggle the CS.
		 */
		spi_writel(as, CSR0, asd->csr);
		spi_writel(as, MR, SPI_BF(PCS, 0x0e) | SPI_BIT(MODFDIS)
				| SPI_BIT(MSTR));
		mr = spi_readl(as, MR);
		gpio_set_value(asd->npcs_pin, active);
	} else {
		u32 cpol = (spi->mode & SPI_CPOL) ? SPI_BIT(CPOL) : 0;
		int i;
		u32 csr;

		/* Make sure clock polarity is correct */
		for (i = 0; i < spi->master->num_chipselect; i++) {
			csr = spi_readl(as, CSR0 + 4 * i);
			if ((csr ^ cpol) & SPI_BIT(CPOL))
				spi_writel(as, CSR0 + 4 * i,
						csr ^ SPI_BIT(CPOL));
		}

		mr = spi_readl(as, MR);
		mr = SPI_BFINS(PCS, ~(1 << spi->chip_select), mr);
		if (spi->chip_select != 0)
			gpio_set_value(asd->npcs_pin, active);
		spi_writel(as, MR, mr);
	}

	dev_dbg(&spi->dev, "activate %u%s, mr %08x\n",
			asd->npcs_pin, active ? " (high)" : "",
			mr);
}