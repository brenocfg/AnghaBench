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
struct spi_device {unsigned int bits_per_word; int chip_select; int mode; int /*<<< orphan*/  dev; struct atmel_spi_device* controller_state; scalar_t__ controller_data; int /*<<< orphan*/  max_speed_hz; TYPE_1__* master; } ;
struct atmel_spi_device {unsigned int npcs_pin; int csr; } ;
struct atmel_spi {int /*<<< orphan*/  lock; struct spi_device* stay; int /*<<< orphan*/  clk; scalar_t__ stopping; } ;
struct TYPE_2__ {int num_chipselect; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS ; 
 int /*<<< orphan*/  CPOL ; 
 scalar_t__ CSR0 ; 
 int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DLYBCT ; 
 int /*<<< orphan*/  DLYBS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NCPHA ; 
 int /*<<< orphan*/  SCBR ; 
 int SPI_BF (int /*<<< orphan*/ ,unsigned int) ; 
 int SPI_BIT (int /*<<< orphan*/ ) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_SCBR_SIZE ; 
 int /*<<< orphan*/  atmel_spi_is_v2 () ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_deactivate (struct atmel_spi*,struct spi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_direction_output (unsigned int,int) ; 
 int gpio_request (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atmel_spi_device*) ; 
 struct atmel_spi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct atmel_spi* spi_master_get_devdata (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_writel (struct atmel_spi*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int atmel_spi_setup(struct spi_device *spi)
{
	struct atmel_spi	*as;
	struct atmel_spi_device	*asd;
	u32			scbr, csr;
	unsigned int		bits = spi->bits_per_word;
	unsigned long		bus_hz;
	unsigned int		npcs_pin;
	int			ret;

	as = spi_master_get_devdata(spi->master);

	if (as->stopping)
		return -ESHUTDOWN;

	if (spi->chip_select > spi->master->num_chipselect) {
		dev_dbg(&spi->dev,
				"setup: invalid chipselect %u (%u defined)\n",
				spi->chip_select, spi->master->num_chipselect);
		return -EINVAL;
	}

	if (bits < 8 || bits > 16) {
		dev_dbg(&spi->dev,
				"setup: invalid bits_per_word %u (8 to 16)\n",
				bits);
		return -EINVAL;
	}

	/* see notes above re chipselect */
	if (!atmel_spi_is_v2()
			&& spi->chip_select == 0
			&& (spi->mode & SPI_CS_HIGH)) {
		dev_dbg(&spi->dev, "setup: can't be active-high\n");
		return -EINVAL;
	}

	/* v1 chips start out at half the peripheral bus speed. */
	bus_hz = clk_get_rate(as->clk);
	if (!atmel_spi_is_v2())
		bus_hz /= 2;

	if (spi->max_speed_hz) {
		/*
		 * Calculate the lowest divider that satisfies the
		 * constraint, assuming div32/fdiv/mbz == 0.
		 */
		scbr = DIV_ROUND_UP(bus_hz, spi->max_speed_hz);

		/*
		 * If the resulting divider doesn't fit into the
		 * register bitfield, we can't satisfy the constraint.
		 */
		if (scbr >= (1 << SPI_SCBR_SIZE)) {
			dev_dbg(&spi->dev,
				"setup: %d Hz too slow, scbr %u; min %ld Hz\n",
				spi->max_speed_hz, scbr, bus_hz/255);
			return -EINVAL;
		}
	} else
		/* speed zero means "as slow as possible" */
		scbr = 0xff;

	csr = SPI_BF(SCBR, scbr) | SPI_BF(BITS, bits - 8);
	if (spi->mode & SPI_CPOL)
		csr |= SPI_BIT(CPOL);
	if (!(spi->mode & SPI_CPHA))
		csr |= SPI_BIT(NCPHA);

	/* DLYBS is mostly irrelevant since we manage chipselect using GPIOs.
	 *
	 * DLYBCT would add delays between words, slowing down transfers.
	 * It could potentially be useful to cope with DMA bottlenecks, but
	 * in those cases it's probably best to just use a lower bitrate.
	 */
	csr |= SPI_BF(DLYBS, 0);
	csr |= SPI_BF(DLYBCT, 0);

	/* chipselect must have been muxed as GPIO (e.g. in board setup) */
	npcs_pin = (unsigned int)spi->controller_data;
	asd = spi->controller_state;
	if (!asd) {
		asd = kzalloc(sizeof(struct atmel_spi_device), GFP_KERNEL);
		if (!asd)
			return -ENOMEM;

		ret = gpio_request(npcs_pin, dev_name(&spi->dev));
		if (ret) {
			kfree(asd);
			return ret;
		}

		asd->npcs_pin = npcs_pin;
		spi->controller_state = asd;
		gpio_direction_output(npcs_pin, !(spi->mode & SPI_CS_HIGH));
	} else {
		unsigned long		flags;

		spin_lock_irqsave(&as->lock, flags);
		if (as->stay == spi)
			as->stay = NULL;
		cs_deactivate(as, spi);
		spin_unlock_irqrestore(&as->lock, flags);
	}

	asd->csr = csr;

	dev_dbg(&spi->dev,
		"setup: %lu Hz bpw %u mode 0x%x -> csr%d %08x\n",
		bus_hz / scbr, bits, spi->mode, spi->chip_select, csr);

	if (!atmel_spi_is_v2())
		spi_writel(as, CSR0 + 4 * spi->chip_select, csr);

	return 0;
}