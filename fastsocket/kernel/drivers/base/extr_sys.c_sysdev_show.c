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
struct sysdev_attribute {int /*<<< orphan*/  (* show ) (struct sys_device*,struct sysdev_attribute*,char*) ;} ;
struct sys_device {int dummy; } ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct sys_device*,struct sysdev_attribute*,char*) ; 
 struct sys_device* to_sysdev (struct kobject*) ; 
 struct sysdev_attribute* to_sysdev_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t
sysdev_show(struct kobject *kobj, struct attribute *attr, char *buffer)
{
	struct sys_device *sysdev = to_sysdev(kobj);
	struct sysdev_attribute *sysdev_attr = to_sysdev_attr(attr);

	if (sysdev_attr->show)
		return sysdev_attr->show(sysdev, sysdev_attr, buffer);
	return -EIO;
}