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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dasd_devmap {int features; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DASD_FEATURE_FAILONSLCK ; 
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dasd_reservation_policy_show(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct dasd_devmap *devmap;
	int rc = 0;

	devmap = dasd_find_busid(dev_name(dev));
	if (IS_ERR(devmap)) {
		rc = snprintf(buf, PAGE_SIZE, "ignore\n");
	} else {
		spin_lock(&dasd_devmap_lock);
		if (devmap->features & DASD_FEATURE_FAILONSLCK)
			rc = snprintf(buf, PAGE_SIZE, "fail\n");
		else
			rc = snprintf(buf, PAGE_SIZE, "ignore\n");
		spin_unlock(&dasd_devmap_lock);
	}
	return rc;
}