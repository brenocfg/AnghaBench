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
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWMON_ID_FORMAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  hwmon_idr ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void hwmon_device_unregister(struct device *dev)
{
	int id;

	if (likely(sscanf(dev_name(dev), HWMON_ID_FORMAT, &id) == 1)) {
		device_unregister(dev);
		spin_lock(&idr_lock);
		idr_remove(&hwmon_idr, id);
		spin_unlock(&idr_lock);
	} else
		dev_dbg(dev->parent,
			"hwmon_device_unregister() failed: bad class ID!\n");
}