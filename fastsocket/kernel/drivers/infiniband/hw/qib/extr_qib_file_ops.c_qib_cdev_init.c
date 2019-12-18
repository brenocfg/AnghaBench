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
struct file_operations {int dummy; } ;
struct device {int dummy; } ;
struct cdev {int /*<<< orphan*/  kobj; struct file_operations const* ops; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (struct cdev*,int /*<<< orphan*/  const,int) ; 
 struct cdev* cdev_alloc () ; 
 int /*<<< orphan*/  cdev_del (struct cdev*) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,int,char const*,...) ; 
 int /*<<< orphan*/  qib_class ; 
 int /*<<< orphan*/  qib_dev ; 

int qib_cdev_init(int minor, const char *name,
		  const struct file_operations *fops,
		  struct cdev **cdevp, struct device **devp)
{
	const dev_t dev = MKDEV(MAJOR(qib_dev), minor);
	struct cdev *cdev;
	struct device *device = NULL;
	int ret;

	cdev = cdev_alloc();
	if (!cdev) {
		pr_err("Could not allocate cdev for minor %d, %s\n",
		       minor, name);
		ret = -ENOMEM;
		goto done;
	}

	cdev->owner = THIS_MODULE;
	cdev->ops = fops;
	kobject_set_name(&cdev->kobj, name);

	ret = cdev_add(cdev, dev, 1);
	if (ret < 0) {
		pr_err("Could not add cdev for minor %d, %s (err %d)\n",
		       minor, name, -ret);
		goto err_cdev;
	}

	device = device_create(qib_class, NULL, dev, NULL, name);
	if (!IS_ERR(device))
		goto done;
	ret = PTR_ERR(device);
	device = NULL;
	pr_err("Could not create device for minor %d, %s (err %d)\n",
	       minor, name, -ret);
err_cdev:
	cdev_del(cdev);
	cdev = NULL;
done:
	*cdevp = cdev;
	*devp = device;
	return ret;
}