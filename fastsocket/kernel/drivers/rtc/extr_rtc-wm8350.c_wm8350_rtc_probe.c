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
typedef  int u16 ;
struct wm8350_rtc {int /*<<< orphan*/  rtc; } ;
struct wm8350 {int /*<<< orphan*/  dev; struct wm8350_rtc rtc; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WM8350_IRQ_RTC_ALM ; 
 int /*<<< orphan*/  WM8350_IRQ_RTC_PER ; 
 int /*<<< orphan*/  WM8350_IRQ_RTC_SEC ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_5 ; 
 int WM8350_RTC_12HR ; 
 int WM8350_RTC_BCD ; 
 int /*<<< orphan*/  WM8350_RTC_SET ; 
 int WM8350_RTC_STS ; 
 int WM8350_RTC_TICK_ENA ; 
 int /*<<< orphan*/  WM8350_RTC_TIME_CONTROL ; 
 int WM8350_SET_TIME_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct wm8350* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_mask_irq (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_lock (struct wm8350*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_unlock (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_register_irq (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8350_rtc_alarm_handler ; 
 int /*<<< orphan*/  wm8350_rtc_ops ; 
 int /*<<< orphan*/  wm8350_rtc_update_handler ; 
 int wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_unmask_irq (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_rtc_probe(struct platform_device *pdev)
{
	struct wm8350 *wm8350 = platform_get_drvdata(pdev);
	struct wm8350_rtc *wm_rtc = &wm8350->rtc;
	int ret = 0;
	u16 timectl, power5;

	timectl = wm8350_reg_read(wm8350, WM8350_RTC_TIME_CONTROL);
	if (timectl & WM8350_RTC_BCD) {
		dev_err(&pdev->dev, "RTC BCD mode not supported\n");
		return -EINVAL;
	}
	if (timectl & WM8350_RTC_12HR) {
		dev_err(&pdev->dev, "RTC 12 hour mode not supported\n");
		return -EINVAL;
	}

	/* enable the RTC if it's not already enabled */
	power5 = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_5);
	if (!(power5 &  WM8350_RTC_TICK_ENA)) {
		dev_info(wm8350->dev, "Starting RTC\n");

		wm8350_reg_unlock(wm8350);

		ret = wm8350_set_bits(wm8350, WM8350_POWER_MGMT_5,
				      WM8350_RTC_TICK_ENA);
		if (ret < 0) {
			dev_err(&pdev->dev, "failed to enable RTC: %d\n", ret);
			return ret;
		}

		wm8350_reg_lock(wm8350);
	}

	if (timectl & WM8350_RTC_STS) {
		int retries;

		ret = wm8350_clear_bits(wm8350, WM8350_RTC_TIME_CONTROL,
					WM8350_RTC_SET);
		if (ret < 0) {
			dev_err(&pdev->dev, "failed to start: %d\n", ret);
			return ret;
		}

		retries = WM8350_SET_TIME_RETRIES;
		do {
			timectl = wm8350_reg_read(wm8350,
						  WM8350_RTC_TIME_CONTROL);
		} while (timectl & WM8350_RTC_STS && --retries);

		if (retries == 0) {
			dev_err(&pdev->dev, "failed to start: timeout\n");
			return -ENODEV;
		}
	}

	device_init_wakeup(&pdev->dev, 1);

	wm_rtc->rtc = rtc_device_register("wm8350", &pdev->dev,
					  &wm8350_rtc_ops, THIS_MODULE);
	if (IS_ERR(wm_rtc->rtc)) {
		ret = PTR_ERR(wm_rtc->rtc);
		dev_err(&pdev->dev, "failed to register RTC: %d\n", ret);
		return ret;
	}

	wm8350_mask_irq(wm8350, WM8350_IRQ_RTC_SEC);
	wm8350_mask_irq(wm8350, WM8350_IRQ_RTC_PER);

	wm8350_register_irq(wm8350, WM8350_IRQ_RTC_SEC,
			    wm8350_rtc_update_handler, NULL);

	wm8350_register_irq(wm8350, WM8350_IRQ_RTC_ALM,
			    wm8350_rtc_alarm_handler, NULL);
	wm8350_unmask_irq(wm8350, WM8350_IRQ_RTC_ALM);

	return 0;
}