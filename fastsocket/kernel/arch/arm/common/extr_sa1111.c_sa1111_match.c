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
struct sa1111_driver {scalar_t__ devid; } ;
struct sa1111_dev {scalar_t__ devid; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sa1111_dev* SA1111_DEV (struct device*) ; 
 struct sa1111_driver* SA1111_DRV (struct device_driver*) ; 

__attribute__((used)) static int sa1111_match(struct device *_dev, struct device_driver *_drv)
{
	struct sa1111_dev *dev = SA1111_DEV(_dev);
	struct sa1111_driver *drv = SA1111_DRV(_drv);

	return dev->devid == drv->devid;
}