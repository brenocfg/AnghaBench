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
struct dasd_device {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct dasd_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 struct dasd_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 

struct dasd_device *
dasd_device_from_cdev_locked(struct ccw_device *cdev)
{
	struct dasd_device *device = dev_get_drvdata(&cdev->dev);

	if (!device)
		return ERR_PTR(-ENODEV);
	dasd_get_device(device);
	return device;
}