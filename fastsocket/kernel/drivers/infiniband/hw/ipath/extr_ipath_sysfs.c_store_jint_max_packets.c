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
struct ipath_devdata {int /*<<< orphan*/  ipath_jint_idle_ticks; int /*<<< orphan*/  (* ipath_f_config_jint ) (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 int ipath_parse_ushort (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store_jint_max_packets(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf,
				      size_t count)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	u16 v = 0;
	int ret;

	ret = ipath_parse_ushort(buf, &v);
	if (ret < 0)
		ipath_dev_err(dd, "invalid jint_max_packets.\n");
	else
		dd->ipath_f_config_jint(dd, dd->ipath_jint_idle_ticks, v);

	return ret;
}