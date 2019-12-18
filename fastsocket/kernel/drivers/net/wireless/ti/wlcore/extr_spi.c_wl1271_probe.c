#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {TYPE_2__* core; TYPE_7__* dev; int /*<<< orphan*/ * if_ops; int /*<<< orphan*/  pdata; } ;
struct wl12xx_spi_glue {TYPE_2__* core; TYPE_7__* dev; int /*<<< orphan*/ * if_ops; int /*<<< orphan*/  pdata; } ;
struct TYPE_10__ {int /*<<< orphan*/  platform_data; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  irq; TYPE_7__ dev; } ;
struct resource {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  res ;
struct TYPE_8__ {TYPE_7__* parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  kfree (struct wlcore_platdev_data*) ; 
 struct wlcore_platdev_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int platform_device_add (TYPE_2__*) ; 
 int platform_device_add_data (TYPE_2__*,struct wlcore_platdev_data*,int) ; 
 int platform_device_add_resources (TYPE_2__*,struct resource*,int /*<<< orphan*/ ) ; 
 TYPE_2__* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_2__*) ; 
 int /*<<< orphan*/  spi_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct wlcore_platdev_data*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int wl1271_probe(struct spi_device *spi)
{
	struct wl12xx_spi_glue *glue;
	struct wlcore_platdev_data *pdev_data;
	struct resource res[1];
	int ret = -ENOMEM;

	pdev_data = kzalloc(sizeof(*pdev_data), GFP_KERNEL);
	if (!pdev_data)
		goto out;

	pdev_data->pdata = spi->dev.platform_data;
	if (!pdev_data->pdata) {
		dev_err(&spi->dev, "no platform data\n");
		ret = -ENODEV;
		goto out_free_pdev_data;
	}

	pdev_data->if_ops = &spi_ops;

	glue = kzalloc(sizeof(*glue), GFP_KERNEL);
	if (!glue) {
		dev_err(&spi->dev, "can't allocate glue\n");
		goto out_free_pdev_data;
	}

	glue->dev = &spi->dev;

	spi_set_drvdata(spi, glue);

	/* This is the only SPI value that we need to set here, the rest
	 * comes from the board-peripherals file */
	spi->bits_per_word = 32;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(glue->dev, "spi_setup failed\n");
		goto out_free_glue;
	}

	glue->core = platform_device_alloc("wl12xx", PLATFORM_DEVID_AUTO);
	if (!glue->core) {
		dev_err(glue->dev, "can't allocate platform_device\n");
		ret = -ENOMEM;
		goto out_free_glue;
	}

	glue->core->dev.parent = &spi->dev;

	memset(res, 0x00, sizeof(res));

	res[0].start = spi->irq;
	res[0].flags = IORESOURCE_IRQ;
	res[0].name = "irq";

	ret = platform_device_add_resources(glue->core, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(glue->dev, "can't add resources\n");
		goto out_dev_put;
	}

	ret = platform_device_add_data(glue->core, pdev_data,
				       sizeof(*pdev_data));
	if (ret) {
		dev_err(glue->dev, "can't add platform data\n");
		goto out_dev_put;
	}

	ret = platform_device_add(glue->core);
	if (ret) {
		dev_err(glue->dev, "can't register platform device\n");
		goto out_dev_put;
	}

	return 0;

out_dev_put:
	platform_device_put(glue->core);

out_free_glue:
	kfree(glue);

out_free_pdev_data:
	kfree(pdev_data);

out:
	return ret;
}