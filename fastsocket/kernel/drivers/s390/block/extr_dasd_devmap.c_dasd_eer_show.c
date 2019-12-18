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
struct dasd_devmap {scalar_t__ device; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dasd_devmap*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int dasd_eer_enabled (scalar_t__) ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
dasd_eer_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dasd_devmap *devmap;
	int eer_flag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_ERR(devmap) && devmap->device)
		eer_flag = dasd_eer_enabled(devmap->device);
	else
		eer_flag = 0;
	return snprintf(buf, PAGE_SIZE, eer_flag ? "1\n" : "0\n");
}