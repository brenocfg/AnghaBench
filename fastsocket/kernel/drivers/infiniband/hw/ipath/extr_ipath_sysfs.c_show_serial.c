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
struct ipath_devdata {int /*<<< orphan*/  ipath_serial; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t show_serial(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);

	buf[sizeof dd->ipath_serial] = '\0';
	memcpy(buf, dd->ipath_serial, sizeof dd->ipath_serial);
	strcat(buf, "\n");
	return strlen(buf);
}