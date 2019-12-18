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
struct gendisk {struct dasd_devmap* private_data; } ;
struct dasd_devmap {struct dasd_device* device; } ;
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_devmap_lock ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dasd_device *dasd_device_from_gendisk(struct gendisk *gdp)
{
	struct dasd_device *device;
	struct dasd_devmap *devmap;

	if (!gdp->private_data)
		return NULL;
	device = NULL;
	spin_lock(&dasd_devmap_lock);
	devmap = gdp->private_data;
	if (devmap && devmap->device) {
		device = devmap->device;
		dasd_get_device(device);
	}
	spin_unlock(&dasd_devmap_lock);
	return device;
}