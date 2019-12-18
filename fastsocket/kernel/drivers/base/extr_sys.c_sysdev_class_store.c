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
struct sysdev_class_attribute {int /*<<< orphan*/  (* store ) (struct sysdev_class*,char const*,size_t) ;} ;
struct sysdev_class {int dummy; } ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct sysdev_class*,char const*,size_t) ; 
 struct sysdev_class* to_sysdev_class (struct kobject*) ; 
 struct sysdev_class_attribute* to_sysdev_class_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t sysdev_class_store(struct kobject *kobj, struct attribute *attr,
				  const char *buffer, size_t count)
{
	struct sysdev_class *class = to_sysdev_class(kobj);
	struct sysdev_class_attribute *class_attr = to_sysdev_class_attr(attr);

	if (class_attr->store)
		return class_attr->store(class, buffer, count);
	return -EIO;
}