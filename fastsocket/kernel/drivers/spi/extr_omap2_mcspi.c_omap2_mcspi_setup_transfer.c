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
typedef  int u8 ;
typedef  int u32 ;
struct spi_transfer {int bits_per_word; } ;
struct spi_master {int dummy; } ;
struct spi_device {int bits_per_word; int max_speed_hz; int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; struct omap2_mcspi_cs* controller_state; } ;
struct omap2_mcspi_cs {int word_len; } ;
struct omap2_mcspi {struct spi_master* master; } ;

/* Variables and functions */
 int OMAP2_MCSPI_CHCONF_CLKD_MASK ; 
 int OMAP2_MCSPI_CHCONF_DPE0 ; 
 int OMAP2_MCSPI_CHCONF_DPE1 ; 
 int OMAP2_MCSPI_CHCONF_EPOL ; 
 int OMAP2_MCSPI_CHCONF_IS ; 
 int OMAP2_MCSPI_CHCONF_PHA ; 
 int OMAP2_MCSPI_CHCONF_POL ; 
 int OMAP2_MCSPI_CHCONF_WL_MASK ; 
 int OMAP2_MCSPI_MAX_FREQ ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,char*,char*) ; 
 int mcspi_cached_chconf0 (struct spi_device*) ; 
 int /*<<< orphan*/  mcspi_write_chconf0 (struct spi_device*,int) ; 
 struct omap2_mcspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_mcspi_setup_transfer(struct spi_device *spi,
		struct spi_transfer *t)
{
	struct omap2_mcspi_cs *cs = spi->controller_state;
	struct omap2_mcspi *mcspi;
	struct spi_master *spi_cntrl;
	u32 l = 0, div = 0;
	u8 word_len = spi->bits_per_word;

	mcspi = spi_master_get_devdata(spi->master);
	spi_cntrl = mcspi->master;

	if (t != NULL && t->bits_per_word)
		word_len = t->bits_per_word;

	cs->word_len = word_len;

	if (spi->max_speed_hz) {
		while (div <= 15 && (OMAP2_MCSPI_MAX_FREQ / (1 << div))
					> spi->max_speed_hz)
			div++;
	} else
		div = 15;

	l = mcspi_cached_chconf0(spi);

	/* standard 4-wire master mode:  SCK, MOSI/out, MISO/in, nCS
	 * REVISIT: this controller could support SPI_3WIRE mode.
	 */
	l &= ~(OMAP2_MCSPI_CHCONF_IS|OMAP2_MCSPI_CHCONF_DPE1);
	l |= OMAP2_MCSPI_CHCONF_DPE0;

	/* wordlength */
	l &= ~OMAP2_MCSPI_CHCONF_WL_MASK;
	l |= (word_len - 1) << 7;

	/* set chipselect polarity; manage with FORCE */
	if (!(spi->mode & SPI_CS_HIGH))
		l |= OMAP2_MCSPI_CHCONF_EPOL;	/* active-low; normal */
	else
		l &= ~OMAP2_MCSPI_CHCONF_EPOL;

	/* set clock divisor */
	l &= ~OMAP2_MCSPI_CHCONF_CLKD_MASK;
	l |= div << 2;

	/* set SPI mode 0..3 */
	if (spi->mode & SPI_CPOL)
		l |= OMAP2_MCSPI_CHCONF_POL;
	else
		l &= ~OMAP2_MCSPI_CHCONF_POL;
	if (spi->mode & SPI_CPHA)
		l |= OMAP2_MCSPI_CHCONF_PHA;
	else
		l &= ~OMAP2_MCSPI_CHCONF_PHA;

	mcspi_write_chconf0(spi, l);

	dev_dbg(&spi->dev, "setup: speed %d, sample %s edge, clk %s\n",
			OMAP2_MCSPI_MAX_FREQ / (1 << div),
			(spi->mode & SPI_CPHA) ? "trailing" : "leading",
			(spi->mode & SPI_CPOL) ? "inverted" : "normal");

	return 0;
}