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
struct rtc_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_attr_irq ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_device*) ; 
 struct rtc_device* rtc_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_device_unregister (struct rtc_device*) ; 
 int /*<<< orphan*/  test_rtc_ops ; 

__attribute__((used)) static int test_probe(struct platform_device *plat_dev)
{
	int err;
	struct rtc_device *rtc = rtc_device_register("test", &plat_dev->dev,
						&test_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc)) {
		err = PTR_ERR(rtc);
		return err;
	}

	err = device_create_file(&plat_dev->dev, &dev_attr_irq);
	if (err)
		goto err;

	platform_set_drvdata(plat_dev, rtc);

	return 0;

err:
	rtc_device_unregister(rtc);
	return err;
}