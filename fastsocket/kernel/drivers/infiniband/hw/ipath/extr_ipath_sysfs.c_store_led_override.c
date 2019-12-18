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
typedef  int /*<<< orphan*/  u16 ;
struct ipath_devdata {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 int ipath_parse_ushort (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_set_led_override (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_led_override(struct device *dev,
			  struct device_attribute *attr,
			  const char *buf,
			  size_t count)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	int ret;
	u16 val;

	ret = ipath_parse_ushort(buf, &val);
	if (ret > 0)
		ipath_set_led_override(dd, val);
	else
		ipath_dev_err(dd, "attempt to set invalid LED override\n");
	return ret;
}