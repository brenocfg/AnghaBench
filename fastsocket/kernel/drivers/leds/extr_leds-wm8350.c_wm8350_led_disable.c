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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct wm8350_led {scalar_t__ enabled; int /*<<< orphan*/  dcdc; TYPE_1__ cdev; int /*<<< orphan*/  isink; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8350_led_disable(struct wm8350_led *led)
{
	int ret;

	if (!led->enabled)
		return;

	ret = regulator_disable(led->dcdc);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to disable DCDC: %d\n", ret);
		return;
	}

	ret = regulator_disable(led->isink);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to disable ISINK: %d\n", ret);
		regulator_enable(led->dcdc);
		return;
	}

	led->enabled = 0;
}