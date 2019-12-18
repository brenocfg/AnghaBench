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
struct wm831x_status {TYPE_1__ cdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_src ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wm831x_status*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 struct wm831x_status* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int wm831x_status_remove(struct platform_device *pdev)
{
	struct wm831x_status *drvdata = platform_get_drvdata(pdev);

	device_remove_file(drvdata->cdev.dev, &dev_attr_src);
	led_classdev_unregister(&drvdata->cdev);
	kfree(drvdata);

	return 0;
}