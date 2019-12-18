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
typedef  int /*<<< orphan*/  u8 ;
struct ipath_devdata {int /*<<< orphan*/  ipath_guid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_guid(struct device *dev,
			 struct device_attribute *attr,
			 char *buf)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	u8 *guid;

	guid = (u8 *) & (dd->ipath_guid);

	return scnprintf(buf, PAGE_SIZE,
			 "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
			 guid[0], guid[1], guid[2], guid[3],
			 guid[4], guid[5], guid[6], guid[7]);
}