#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {TYPE_5__* core; int /*<<< orphan*/ * dev; TYPE_4__* pdata; int /*<<< orphan*/ * if_ops; } ;
struct wl12xx_sdio_glue {TYPE_5__* core; int /*<<< orphan*/ * dev; TYPE_4__* pdata; int /*<<< orphan*/ * if_ops; } ;
struct sdio_func {int num; int /*<<< orphan*/  dev; TYPE_2__* card; } ;
struct sdio_device_id {int dummy; } ;
struct resource {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int mmc_pm_flag_t ;
struct TYPE_14__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_16__ {TYPE_3__ dev; } ;
struct TYPE_15__ {int pwr_in_suspend; int /*<<< orphan*/  irq; } ;
struct TYPE_12__ {scalar_t__ sdio_vsn; } ;
struct TYPE_13__ {TYPE_1__ cccr; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int MMC_PM_KEEP_POWER ; 
 int /*<<< orphan*/  MMC_QUIRK_BLKSZ_FOR_BYTE_MODE ; 
 int /*<<< orphan*/  MMC_QUIRK_LENIENT_FN0 ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (TYPE_4__*) ; 
 scalar_t__ SDIO_SDIO_REV_3_00 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (struct wlcore_platdev_data*) ; 
 struct wlcore_platdev_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int platform_device_add (TYPE_5__*) ; 
 int platform_device_add_data (TYPE_5__*,struct wlcore_platdev_data*,int) ; 
 int platform_device_add_resources (TYPE_5__*,struct resource*,int /*<<< orphan*/ ) ; 
 TYPE_5__* platform_device_alloc (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_5__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int sdio_get_host_pm_caps (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_ops ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct wlcore_platdev_data*) ; 
 TYPE_4__* wl12xx_get_platform_data () ; 

__attribute__((used)) static int wl1271_probe(struct sdio_func *func,
				  const struct sdio_device_id *id)
{
	struct wlcore_platdev_data *pdev_data;
	struct wl12xx_sdio_glue *glue;
	struct resource res[1];
	mmc_pm_flag_t mmcflags;
	int ret = -ENOMEM;
	const char *chip_family;

	/* We are only able to handle the wlan function */
	if (func->num != 0x02)
		return -ENODEV;

	pdev_data = kzalloc(sizeof(*pdev_data), GFP_KERNEL);
	if (!pdev_data)
		goto out;

	pdev_data->if_ops = &sdio_ops;

	glue = kzalloc(sizeof(*glue), GFP_KERNEL);
	if (!glue) {
		dev_err(&func->dev, "can't allocate glue\n");
		goto out_free_pdev_data;
	}

	glue->dev = &func->dev;

	/* Grab access to FN0 for ELP reg. */
	func->card->quirks |= MMC_QUIRK_LENIENT_FN0;

	/* Use block mode for transferring over one block size of data */
	func->card->quirks |= MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;

	pdev_data->pdata = wl12xx_get_platform_data();
	if (IS_ERR(pdev_data->pdata)) {
		ret = PTR_ERR(pdev_data->pdata);
		dev_err(glue->dev, "missing wlan platform data: %d\n", ret);
		goto out_free_glue;
	}

	/* if sdio can keep power while host is suspended, enable wow */
	mmcflags = sdio_get_host_pm_caps(func);
	dev_dbg(glue->dev, "sdio PM caps = 0x%x\n", mmcflags);

	if (mmcflags & MMC_PM_KEEP_POWER)
		pdev_data->pdata->pwr_in_suspend = true;

	sdio_set_drvdata(func, glue);

	/* Tell PM core that we don't need the card to be powered now */
	pm_runtime_put_noidle(&func->dev);

	/*
	 * Due to a hardware bug, we can't differentiate wl18xx from
	 * wl12xx, because both report the same device ID.  The only
	 * way to differentiate is by checking the SDIO revision,
	 * which is 3.00 on the wl18xx chips.
	 */
	if (func->card->cccr.sdio_vsn == SDIO_SDIO_REV_3_00)
		chip_family = "wl18xx";
	else
		chip_family = "wl12xx";

	glue->core = platform_device_alloc(chip_family, PLATFORM_DEVID_AUTO);
	if (!glue->core) {
		dev_err(glue->dev, "can't allocate platform_device");
		ret = -ENOMEM;
		goto out_free_glue;
	}

	glue->core->dev.parent = &func->dev;

	memset(res, 0x00, sizeof(res));

	res[0].start = pdev_data->pdata->irq;
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
		dev_err(glue->dev, "can't add platform device\n");
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