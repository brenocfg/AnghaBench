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
struct ipath_devdata {int /*<<< orphan*/ * ipath_eep_st_errs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENXIO ; 
 int IPATH_EEP_LOG_CNT ; 
 scalar_t__ PAGE_SIZE ; 
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 scalar_t__ ipath_update_eeprom_log (struct ipath_devdata*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static ssize_t show_logged_errs(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	int idx, count;

	/* force consistency with actual EEPROM */
	if (ipath_update_eeprom_log(dd) != 0)
		return -ENXIO;

	count = 0;
	for (idx = 0; idx < IPATH_EEP_LOG_CNT; ++idx) {
		count += scnprintf(buf + count, PAGE_SIZE - count, "%d%c",
			dd->ipath_eep_st_errs[idx],
			idx == (IPATH_EEP_LOG_CNT - 1) ? '\n' : ' ');
	}

	return count;
}