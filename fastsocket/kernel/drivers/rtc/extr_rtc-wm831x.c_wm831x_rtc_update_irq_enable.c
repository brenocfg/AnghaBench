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
struct wm831x_rtc {int /*<<< orphan*/  wm831x; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_RTC_CONTROL ; 
 int /*<<< orphan*/  WM831X_RTC_PINT_FREQ_MASK ; 
 int WM831X_RTC_PINT_FREQ_SHIFT ; 
 struct wm831x_rtc* dev_get_drvdata (struct device*) ; 
 int wm831x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm831x_rtc_update_irq_enable(struct device *dev,
					unsigned int enabled)
{
	struct wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	int val;

	if (enabled)
		val = 1 << WM831X_RTC_PINT_FREQ_SHIFT;
	else
		val = 0;

	return wm831x_set_bits(wm831x_rtc->wm831x, WM831X_RTC_CONTROL,
			       WM831X_RTC_PINT_FREQ_MASK, val);
}