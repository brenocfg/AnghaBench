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
typedef  int u16 ;
struct wm8400_platform_data {int (* platform_init ) (int /*<<< orphan*/ ) ;} ;
struct wm8400 {int (* read_dev ) (int /*<<< orphan*/ ,size_t,int,int*) ;int* reg_cache; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_data; int /*<<< orphan*/  io_lock; } ;
struct TYPE_2__ {scalar_t__ default_val; scalar_t__ is_codec; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EIO ; 
 int ENODEV ; 
 int WM8400_CHIP_REV_MASK ; 
 int WM8400_CHIP_REV_SHIFT ; 
 int WM8400_CODEC_ENA ; 
 int /*<<< orphan*/  WM8400_ID ; 
 size_t WM8400_POWER_MANAGEMENT_1 ; 
 size_t WM8400_RESET_ID ; 
 int be16_to_cpu (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct wm8400*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* reg_data ; 
 int stub1 (int /*<<< orphan*/ ,size_t,int,int*) ; 
 int stub2 (int /*<<< orphan*/ ,size_t,int,int*) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int wm8400_read (struct wm8400*,int /*<<< orphan*/ ,int,int*) ; 
 int wm8400_register_codec (struct wm8400*) ; 

__attribute__((used)) static int wm8400_init(struct wm8400 *wm8400,
		       struct wm8400_platform_data *pdata)
{
	u16 reg;
	int ret, i;

	mutex_init(&wm8400->io_lock);

	dev_set_drvdata(wm8400->dev, wm8400);

	/* Check that this is actually a WM8400 */
	ret = wm8400->read_dev(wm8400->io_data, WM8400_RESET_ID, 1, &reg);
	if (ret != 0) {
		dev_err(wm8400->dev, "Chip ID register read failed\n");
		return -EIO;
	}
	if (be16_to_cpu(reg) != reg_data[WM8400_RESET_ID].default_val) {
		dev_err(wm8400->dev, "Device is not a WM8400, ID is %x\n",
			be16_to_cpu(reg));
		return -ENODEV;
	}

	/* We don't know what state the hardware is in and since this
	 * is a PMIC we can't reset it safely so initialise the register
	 * cache from the hardware.
	 */
	ret = wm8400->read_dev(wm8400->io_data, 0,
			       ARRAY_SIZE(wm8400->reg_cache),
			       wm8400->reg_cache);
	if (ret != 0) {
		dev_err(wm8400->dev, "Register cache read failed\n");
		return -EIO;
	}
	for (i = 0; i < ARRAY_SIZE(wm8400->reg_cache); i++)
		wm8400->reg_cache[i] = be16_to_cpu(wm8400->reg_cache[i]);

	/* If the codec is in reset use hard coded values */
	if (!(wm8400->reg_cache[WM8400_POWER_MANAGEMENT_1] & WM8400_CODEC_ENA))
		for (i = 0; i < ARRAY_SIZE(wm8400->reg_cache); i++)
			if (reg_data[i].is_codec)
				wm8400->reg_cache[i] = reg_data[i].default_val;

	ret = wm8400_read(wm8400, WM8400_ID, 1, &reg);
	if (ret != 0) {
		dev_err(wm8400->dev, "ID register read failed: %d\n", ret);
		return ret;
	}
	reg = (reg & WM8400_CHIP_REV_MASK) >> WM8400_CHIP_REV_SHIFT;
	dev_info(wm8400->dev, "WM8400 revision %x\n", reg);

	ret = wm8400_register_codec(wm8400);
	if (ret != 0) {
		dev_err(wm8400->dev, "Failed to register codec\n");
		goto err_children;
	}

	if (pdata && pdata->platform_init) {
		ret = pdata->platform_init(wm8400->dev);
		if (ret != 0) {
			dev_err(wm8400->dev, "Platform init failed: %d\n",
				ret);
			goto err_children;
		}
	} else
		dev_warn(wm8400->dev, "No platform initialisation supplied\n");

	return 0;

err_children:
	mfd_remove_devices(wm8400->dev);
	return ret;
}