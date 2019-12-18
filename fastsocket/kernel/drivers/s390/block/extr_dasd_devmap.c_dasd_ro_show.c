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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DASD_FEATURE_DEFAULT ; 
 int DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  IS_ERR (struct dasd_devmap*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
dasd_ro_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dasd_devmap *devmap;
	int ro_flag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_ERR(devmap))
		ro_flag = (devmap->features & DASD_FEATURE_READONLY) != 0;
	else
		ro_flag = (DASD_FEATURE_DEFAULT & DASD_FEATURE_READONLY) != 0;
	return snprintf(buf, PAGE_SIZE, ro_flag ? "1\n" : "0\n");
}