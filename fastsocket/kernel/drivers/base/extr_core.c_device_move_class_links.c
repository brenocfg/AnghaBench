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
struct device {int /*<<< orphan*/  kobj; TYPE_1__* class; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* make_class_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int device_move_class_links(struct device *dev,
				   struct device *old_parent,
				   struct device *new_parent)
{
	int error = 0;
#ifdef CONFIG_SYSFS_DEPRECATED
	char *class_name;

	class_name = make_class_name(dev->class->name, &dev->kobj);
	if (!class_name) {
		error = -ENOMEM;
		goto out;
	}
	if (old_parent) {
		sysfs_remove_link(&dev->kobj, "device");
		sysfs_remove_link(&old_parent->kobj, class_name);
	}
	if (new_parent) {
		error = sysfs_create_link(&dev->kobj, &new_parent->kobj,
					  "device");
		if (error)
			goto out;
		error = sysfs_create_link(&new_parent->kobj, &dev->kobj,
					  class_name);
		if (error)
			sysfs_remove_link(&dev->kobj, "device");
	} else
		error = 0;
out:
	kfree(class_name);
	return error;
#else
	if (old_parent)
		sysfs_remove_link(&dev->kobj, "device");
	if (new_parent)
		error = sysfs_create_link(&dev->kobj, &new_parent->kobj,
					  "device");
	return error;
#endif
}