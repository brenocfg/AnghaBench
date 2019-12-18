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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct bmc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __find_bmc_guid ; 
 struct bmc_device* dev_get_drvdata (struct device*) ; 
 struct device* driver_find_device (struct device_driver*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bmc_device *ipmi_find_bmc_guid(struct device_driver *drv,
					     unsigned char *guid)
{
	struct device *dev;

	dev = driver_find_device(drv, NULL, guid, __find_bmc_guid);
	if (dev)
		return dev_get_drvdata(dev);
	else
		return NULL;
}