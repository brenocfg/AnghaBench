#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* parent; } ;
struct device {TYPE_4__ kobj; TYPE_3__* class; struct device* parent; int /*<<< orphan*/  bus; } ;
struct TYPE_10__ {TYPE_2__* p; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_4__ kobj; } ;
struct TYPE_9__ {TYPE_1__ class_subsys; } ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 scalar_t__ device_is_not_partition (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* make_class_name (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int sysfs_create_link (TYPE_4__*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (TYPE_4__*,char*) ; 

__attribute__((used)) static int device_add_class_symlinks(struct device *dev)
{
	int error;

	if (!dev->class)
		return 0;

	error = sysfs_create_link(&dev->kobj,
				  &dev->class->p->class_subsys.kobj,
				  "subsystem");
	if (error)
		goto out;

#ifdef CONFIG_SYSFS_DEPRECATED
	/* stacked class devices need a symlink in the class directory */
	if (dev->kobj.parent != &dev->class->p->class_subsys.kobj &&
	    device_is_not_partition(dev)) {
		error = sysfs_create_link(&dev->class->p->class_subsys.kobj,
					  &dev->kobj, dev_name(dev));
		if (error)
			goto out_subsys;
	}

	if (dev->parent && device_is_not_partition(dev)) {
		struct device *parent = dev->parent;
		char *class_name;

		/*
		 * stacked class devices have the 'device' link
		 * pointing to the bus device instead of the parent
		 */
		while (parent->class && !parent->bus && parent->parent)
			parent = parent->parent;

		error = sysfs_create_link(&dev->kobj,
					  &parent->kobj,
					  "device");
		if (error)
			goto out_busid;

		class_name = make_class_name(dev->class->name,
						&dev->kobj);
		if (class_name)
			error = sysfs_create_link(&dev->parent->kobj,
						&dev->kobj, class_name);
		kfree(class_name);
		if (error)
			goto out_device;
	}
	return 0;

out_device:
	if (dev->parent && device_is_not_partition(dev))
		sysfs_remove_link(&dev->kobj, "device");
out_busid:
	if (dev->kobj.parent != &dev->class->p->class_subsys.kobj &&
	    device_is_not_partition(dev))
		sysfs_remove_link(&dev->class->p->class_subsys.kobj,
				  dev_name(dev));
#else
	/* link in the class directory pointing to the device */
	error = sysfs_create_link(&dev->class->p->class_subsys.kobj,
				  &dev->kobj, dev_name(dev));
	if (error)
		goto out_subsys;

	if (dev->parent && device_is_not_partition(dev)) {
		error = sysfs_create_link(&dev->kobj, &dev->parent->kobj,
					  "device");
		if (error)
			goto out_busid;
	}
	return 0;

out_busid:
	sysfs_remove_link(&dev->class->p->class_subsys.kobj, dev_name(dev));
#endif

out_subsys:
	sysfs_remove_link(&dev->kobj, "subsystem");
out:
	return error;
}