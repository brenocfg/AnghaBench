#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/ * bus; } ;
struct ccw_device {TYPE_2__* private; struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {TYPE_1__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_bus_type ; 
 int dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 

__attribute__((used)) static int ccw_device_register(struct ccw_device *cdev)
{
	struct device *dev = &cdev->dev;
	int ret;

	dev->bus = &ccw_bus_type;
	ret = dev_set_name(&cdev->dev, "0.%x.%04x", cdev->private->dev_id.ssid,
			   cdev->private->dev_id.devno);
	if (ret)
		return ret;
	return device_add(dev);
}