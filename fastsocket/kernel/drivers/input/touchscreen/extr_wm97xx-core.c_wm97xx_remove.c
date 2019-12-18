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
struct wm97xx {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  touch_dev; int /*<<< orphan*/  battery_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct wm97xx* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wm97xx*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm97xx_remove(struct device *dev)
{
	struct wm97xx *wm = dev_get_drvdata(dev);

	platform_device_unregister(wm->battery_dev);
	platform_device_unregister(wm->touch_dev);
	input_unregister_device(wm->input_dev);
	kfree(wm);

	return 0;
}