#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int dummy; } ;
struct s3c2410_spigpio_info {scalar_t__ pin_clk; scalar_t__ pin_mosi; scalar_t__ pin_miso; int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; } ;
struct TYPE_7__ {TYPE_1__* master; int /*<<< orphan*/ * txrx_word; int /*<<< orphan*/  chipselect; } ;
struct s3c2410_spigpio {TYPE_3__ bitbang; struct s3c2410_spigpio_info* info; } ;
struct TYPE_8__ {struct s3c2410_spigpio_info* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_chipselect; int /*<<< orphan*/  bus_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ S3C2410_GPA0 ; 
 scalar_t__ S3C2410_GPH10 ; 
 int /*<<< orphan*/  S3C2410_GPIO_INPUT ; 
 int /*<<< orphan*/  S3C2410_GPIO_OUTPUT ; 
 size_t SPI_MODE_0 ; 
 size_t SPI_MODE_1 ; 
 size_t SPI_MODE_2 ; 
 size_t SPI_MODE_3 ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s3c2410_spigpio*) ; 
 int /*<<< orphan*/  s3c2410_gpio_cfgpin (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_gpio_setpin (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_spigpio_chipselect ; 
 int /*<<< orphan*/  s3c2410_spigpio_txrx_mode0 ; 
 int /*<<< orphan*/  s3c2410_spigpio_txrx_mode1 ; 
 int /*<<< orphan*/  s3c2410_spigpio_txrx_mode2 ; 
 int /*<<< orphan*/  s3c2410_spigpio_txrx_mode3 ; 
 struct spi_master* spi_alloc_master (TYPE_4__*,int) ; 
 int spi_bitbang_start (TYPE_3__*) ; 
 TYPE_1__* spi_master_get (struct spi_master*) ; 
 struct s3c2410_spigpio* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (TYPE_1__*) ; 

__attribute__((used)) static int s3c2410_spigpio_probe(struct platform_device *dev)
{
	struct s3c2410_spigpio_info *info;
	struct spi_master	*master;
	struct s3c2410_spigpio  *sp;
	int ret;

	master = spi_alloc_master(&dev->dev, sizeof(struct s3c2410_spigpio));
	if (master == NULL) {
		dev_err(&dev->dev, "failed to allocate spi master\n");
		ret = -ENOMEM;
		goto err;
	}

	sp = spi_master_get_devdata(master);

	platform_set_drvdata(dev, sp);

	/* copy in the plkatform data */
	info = sp->info = dev->dev.platform_data;

	/* setup spi bitbang adaptor */
	sp->bitbang.master = spi_master_get(master);
	sp->bitbang.master->bus_num = info->bus_num;
	sp->bitbang.master->num_chipselect = info->num_chipselect;
	sp->bitbang.chipselect = s3c2410_spigpio_chipselect;

	sp->bitbang.txrx_word[SPI_MODE_0] = s3c2410_spigpio_txrx_mode0;
	sp->bitbang.txrx_word[SPI_MODE_1] = s3c2410_spigpio_txrx_mode1;
	sp->bitbang.txrx_word[SPI_MODE_2] = s3c2410_spigpio_txrx_mode2;
	sp->bitbang.txrx_word[SPI_MODE_3] = s3c2410_spigpio_txrx_mode3;

	/* set state of spi pins, always assume that the clock is
	 * available, but do check the MOSI and MISO. */
	s3c2410_gpio_setpin(info->pin_clk, 0);
	s3c2410_gpio_cfgpin(info->pin_clk, S3C2410_GPIO_OUTPUT);

	if (info->pin_mosi < S3C2410_GPH10) {
		s3c2410_gpio_setpin(info->pin_mosi, 0);
		s3c2410_gpio_cfgpin(info->pin_mosi, S3C2410_GPIO_OUTPUT);
	}

	if (info->pin_miso != S3C2410_GPA0 && info->pin_miso < S3C2410_GPH10)
		s3c2410_gpio_cfgpin(info->pin_miso, S3C2410_GPIO_INPUT);

	ret = spi_bitbang_start(&sp->bitbang);
	if (ret)
		goto err_no_bitbang;

	return 0;

 err_no_bitbang:
	spi_master_put(sp->bitbang.master);
 err:
	return ret;

}