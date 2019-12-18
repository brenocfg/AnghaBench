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
struct TYPE_2__ {int dev; } ;
struct watchdog_device {int /*<<< orphan*/ * dev; int /*<<< orphan*/  id; TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  watchdog_class ; 
 int watchdog_dev_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_ida ; 

void watchdog_unregister_device(struct watchdog_device *wdd)
{
	int ret;
	int devno;

	if (wdd == NULL)
		return;

	devno = wdd->cdev.dev;
	ret = watchdog_dev_unregister(wdd);
	if (ret)
		pr_err("error unregistering /dev/watchdog (err=%d)\n", ret);
	device_destroy(watchdog_class, devno);
	ida_simple_remove(&watchdog_ida, wdd->id);
	wdd->dev = NULL;
}