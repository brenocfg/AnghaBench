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
struct file_operations {int /*<<< orphan*/  owner; } ;
struct char_device_struct {int major; struct cdev* cdev; } ;
struct cdev {int /*<<< orphan*/  kobj; struct file_operations const* ops; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct char_device_struct*) ; 
 int /*<<< orphan*/  MKDEV (int,unsigned int) ; 
 int PTR_ERR (struct char_device_struct*) ; 
 struct char_device_struct* __register_chrdev_region (unsigned int,unsigned int,unsigned int,char const*) ; 
 int /*<<< orphan*/  __unregister_chrdev_region (int,unsigned int,unsigned int) ; 
 int cdev_add (struct cdev*,int /*<<< orphan*/ ,unsigned int) ; 
 struct cdev* cdev_alloc () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char*,char const*) ; 

int __register_chrdev(unsigned int major, unsigned int baseminor,
		      unsigned int count, const char *name,
		      const struct file_operations *fops)
{
	struct char_device_struct *cd;
	struct cdev *cdev;
	int err = -ENOMEM;

	cd = __register_chrdev_region(major, baseminor, count, name);
	if (IS_ERR(cd))
		return PTR_ERR(cd);
	
	cdev = cdev_alloc();
	if (!cdev)
		goto out2;

	cdev->owner = fops->owner;
	cdev->ops = fops;
	kobject_set_name(&cdev->kobj, "%s", name);
		
	err = cdev_add(cdev, MKDEV(cd->major, baseminor), count);
	if (err)
		goto out;

	cd->cdev = cdev;

	return major ? 0 : cd->major;
out:
	kobject_put(&cdev->kobj);
out2:
	kfree(__unregister_chrdev_region(cd->major, baseminor, count));
	return err;
}