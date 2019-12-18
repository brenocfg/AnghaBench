#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int bits_per_word; int mode; int chip_select; int /*<<< orphan*/  modalias; TYPE_2__* master; int /*<<< orphan*/  dev; int /*<<< orphan*/  max_speed_hz; struct bfin5xx_spi_chip* controller_data; } ;
struct driver_data {int dma_requested; int /*<<< orphan*/  dma_channel; TYPE_1__* master_info; } ;
struct chip_data {int enable_dma; int ctl_reg; int bits_per_word; int flag; int chip_select_num; int n_bytes; int /*<<< orphan*/  width; int /*<<< orphan*/  cs_change_per_word; int /*<<< orphan*/  duplex; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  baud; int /*<<< orphan*/  idle_tx_val; int /*<<< orphan*/  cs_chg_udelay; } ;
struct bfin5xx_spi_chip {int ctl_reg; scalar_t__ enable_dma; int bits_per_word; int /*<<< orphan*/  idle_tx_val; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  cs_chg_udelay; int /*<<< orphan*/  cs_change_per_word; } ;
struct TYPE_4__ {int num_chipselect; size_t bus_num; } ;
struct TYPE_3__ {scalar_t__ enable_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_SPI_WORDSIZE16 ; 
 int /*<<< orphan*/  CFG_SPI_WORDSIZE8 ; 
 int CPHA ; 
 int CPOL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LSBF ; 
 int MSTR ; 
 int SIZE ; 
 int SPE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  bfin_spi_cs_deactive (struct driver_data*,struct chip_data*) ; 
 int /*<<< orphan*/  bfin_spi_dma_irq_handler ; 
 int /*<<< orphan*/  bfin_spi_u16_cs_chg_duplex ; 
 int /*<<< orphan*/  bfin_spi_u16_cs_chg_reader ; 
 int /*<<< orphan*/  bfin_spi_u16_cs_chg_writer ; 
 int /*<<< orphan*/  bfin_spi_u16_duplex ; 
 int /*<<< orphan*/  bfin_spi_u16_reader ; 
 int /*<<< orphan*/  bfin_spi_u16_writer ; 
 int /*<<< orphan*/  bfin_spi_u8_cs_chg_duplex ; 
 int /*<<< orphan*/  bfin_spi_u8_cs_chg_reader ; 
 int /*<<< orphan*/  bfin_spi_u8_cs_chg_writer ; 
 int /*<<< orphan*/  bfin_spi_u8_duplex ; 
 int /*<<< orphan*/  bfin_spi_u8_reader ; 
 int /*<<< orphan*/  bfin_spi_u8_writer ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz_to_spi_baud (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 struct chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peripheral_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_dma (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ set_dma_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct driver_data*) ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 struct driver_data* spi_master_get_devdata (TYPE_2__*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct chip_data*) ; 
 int /*<<< orphan*/ ** ssel ; 

__attribute__((used)) static int bfin_spi_setup(struct spi_device *spi)
{
	struct bfin5xx_spi_chip *chip_info = NULL;
	struct chip_data *chip;
	struct driver_data *drv_data = spi_master_get_devdata(spi->master);
	int ret;

	if (spi->bits_per_word != 8 && spi->bits_per_word != 16)
		return -EINVAL;

	/* Only alloc (or use chip_info) on first setup */
	chip = spi_get_ctldata(spi);
	if (chip == NULL) {
		chip = kzalloc(sizeof(struct chip_data), GFP_KERNEL);
		if (!chip)
			return -ENOMEM;

		chip->enable_dma = 0;
		chip_info = spi->controller_data;
	}

	/* chip_info isn't always needed */
	if (chip_info) {
		/* Make sure people stop trying to set fields via ctl_reg
		 * when they should actually be using common SPI framework.
		 * Currently we let through: WOM EMISO PSSE GM SZ TIMOD.
		 * Not sure if a user actually needs/uses any of these,
		 * but let's assume (for now) they do.
		 */
		if (chip_info->ctl_reg & (SPE|MSTR|CPOL|CPHA|LSBF|SIZE)) {
			dev_err(&spi->dev, "do not set bits in ctl_reg "
				"that the SPI framework manages\n");
			return -EINVAL;
		}

		chip->enable_dma = chip_info->enable_dma != 0
		    && drv_data->master_info->enable_dma;
		chip->ctl_reg = chip_info->ctl_reg;
		chip->bits_per_word = chip_info->bits_per_word;
		chip->cs_change_per_word = chip_info->cs_change_per_word;
		chip->cs_chg_udelay = chip_info->cs_chg_udelay;
		chip->cs_gpio = chip_info->cs_gpio;
		chip->idle_tx_val = chip_info->idle_tx_val;
	}

	/* translate common spi framework into our register */
	if (spi->mode & SPI_CPOL)
		chip->ctl_reg |= CPOL;
	if (spi->mode & SPI_CPHA)
		chip->ctl_reg |= CPHA;
	if (spi->mode & SPI_LSB_FIRST)
		chip->ctl_reg |= LSBF;
	/* we dont support running in slave mode (yet?) */
	chip->ctl_reg |= MSTR;

	/*
	 * if any one SPI chip is registered and wants DMA, request the
	 * DMA channel for it
	 */
	if (chip->enable_dma && !drv_data->dma_requested) {
		/* register dma irq handler */
		if (request_dma(drv_data->dma_channel, "BFIN_SPI_DMA") < 0) {
			dev_dbg(&spi->dev,
				"Unable to request BlackFin SPI DMA channel\n");
			return -ENODEV;
		}
		if (set_dma_callback(drv_data->dma_channel,
		    bfin_spi_dma_irq_handler, drv_data) < 0) {
			dev_dbg(&spi->dev, "Unable to set dma callback\n");
			return -EPERM;
		}
		dma_disable_irq(drv_data->dma_channel);
		drv_data->dma_requested = 1;
	}

	/*
	 * Notice: for blackfin, the speed_hz is the value of register
	 * SPI_BAUD, not the real baudrate
	 */
	chip->baud = hz_to_spi_baud(spi->max_speed_hz);
	chip->flag = 1 << (spi->chip_select);
	chip->chip_select_num = spi->chip_select;

	if (chip->chip_select_num == 0) {
		ret = gpio_request(chip->cs_gpio, spi->modalias);
		if (ret) {
			if (drv_data->dma_requested)
				free_dma(drv_data->dma_channel);
			return ret;
		}
		gpio_direction_output(chip->cs_gpio, 1);
	}

	switch (chip->bits_per_word) {
	case 8:
		chip->n_bytes = 1;
		chip->width = CFG_SPI_WORDSIZE8;
		chip->read = chip->cs_change_per_word ?
			bfin_spi_u8_cs_chg_reader : bfin_spi_u8_reader;
		chip->write = chip->cs_change_per_word ?
			bfin_spi_u8_cs_chg_writer : bfin_spi_u8_writer;
		chip->duplex = chip->cs_change_per_word ?
			bfin_spi_u8_cs_chg_duplex : bfin_spi_u8_duplex;
		break;

	case 16:
		chip->n_bytes = 2;
		chip->width = CFG_SPI_WORDSIZE16;
		chip->read = chip->cs_change_per_word ?
			bfin_spi_u16_cs_chg_reader : bfin_spi_u16_reader;
		chip->write = chip->cs_change_per_word ?
			bfin_spi_u16_cs_chg_writer : bfin_spi_u16_writer;
		chip->duplex = chip->cs_change_per_word ?
			bfin_spi_u16_cs_chg_duplex : bfin_spi_u16_duplex;
		break;

	default:
		dev_err(&spi->dev, "%d bits_per_word is not supported\n",
				chip->bits_per_word);
		if (chip_info)
			kfree(chip);
		return -ENODEV;
	}

	dev_dbg(&spi->dev, "setup spi chip %s, width is %d, dma is %d\n",
			spi->modalias, chip->width, chip->enable_dma);
	dev_dbg(&spi->dev, "ctl_reg is 0x%x, flag_reg is 0x%x\n",
			chip->ctl_reg, chip->flag);

	spi_set_ctldata(spi, chip);

	dev_dbg(&spi->dev, "chip select number is %d\n", chip->chip_select_num);
	if ((chip->chip_select_num > 0)
		&& (chip->chip_select_num <= spi->master->num_chipselect))
		peripheral_request(ssel[spi->master->bus_num]
			[chip->chip_select_num-1], spi->modalias);

	bfin_spi_cs_deactive(drv_data, chip);

	return 0;
}