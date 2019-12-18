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
struct ssb_driver {struct ssb_device_id* id_table; } ;
struct ssb_device_id {scalar_t__ revision; scalar_t__ coreid; scalar_t__ vendor; } ;
struct ssb_device {int /*<<< orphan*/  id; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ssb_device* dev_to_ssb_dev (struct device*) ; 
 struct ssb_driver* drv_to_ssb_drv (struct device_driver*) ; 
 scalar_t__ ssb_match_devid (struct ssb_device_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssb_bus_match(struct device *dev, struct device_driver *drv)
{
	struct ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	struct ssb_driver *ssb_drv = drv_to_ssb_drv(drv);
	const struct ssb_device_id *id;

	for (id = ssb_drv->id_table;
	     id->vendor || id->coreid || id->revision;
	     id++) {
		if (ssb_match_devid(id, &ssb_dev->id))
			return 1; /* found */
	}

	return 0;
}