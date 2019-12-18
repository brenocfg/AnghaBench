#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uio_device {TYPE_1__* info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct uio_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_version(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	struct uio_device *idev = dev_get_drvdata(dev);
	if (idev)
		return sprintf(buf, "%s\n", idev->info->version);
	else
		return -ENODEV;
}