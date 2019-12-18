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
struct maple_device_specify {scalar_t__ port; scalar_t__ unit; } ;
struct maple_device {scalar_t__ port; scalar_t__ unit; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct maple_device* to_maple_dev (struct device*) ; 

__attribute__((used)) static int check_maple_device(struct device *device, void *portptr)
{
	struct maple_device_specify *ds;
	struct maple_device *mdev;

	ds = portptr;
	mdev = to_maple_dev(device);
	if (mdev->port == ds->port && mdev->unit == ds->unit)
		return 1;
	return 0;
}