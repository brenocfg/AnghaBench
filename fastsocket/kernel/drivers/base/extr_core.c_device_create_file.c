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
struct device_attribute {int /*<<< orphan*/  attr; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int device_create_file(struct device *dev, struct device_attribute *attr)
{
	int error = 0;
	if (dev)
		error = sysfs_create_file(&dev->kobj, &attr->attr);
	return error;
}