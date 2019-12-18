#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct tty_driver {int flags; int num; int /*<<< orphan*/  tty_drivers; struct ktermios** termios; struct tty_struct** ttys; TYPE_1__ cdev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; int /*<<< orphan*/  minor_start; scalar_t__ major; } ;
struct ktermios {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int TTY_DRIVER_DEVPTS_MEM ; 
 int TTY_DRIVER_DYNAMIC_DEV ; 
 int TTY_DRIVER_INSTALLED ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_tty_register_driver (struct tty_driver*) ; 
 int register_chrdev_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_drivers ; 
 int /*<<< orphan*/  tty_fops ; 
 int /*<<< orphan*/  tty_mutex ; 
 int /*<<< orphan*/  tty_register_device (struct tty_driver*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

int tty_register_driver(struct tty_driver *driver)
{
	int error;
	int i;
	dev_t dev;
	void **p = NULL;

	if (!(driver->flags & TTY_DRIVER_DEVPTS_MEM) && driver->num) {
		p = kzalloc(driver->num * 2 * sizeof(void *), GFP_KERNEL);
		if (!p)
			return -ENOMEM;
	}

	if (!driver->major) {
		error = alloc_chrdev_region(&dev, driver->minor_start,
						driver->num, driver->name);
		if (!error) {
			driver->major = MAJOR(dev);
			driver->minor_start = MINOR(dev);
		}
	} else {
		dev = MKDEV(driver->major, driver->minor_start);
		error = register_chrdev_region(dev, driver->num, driver->name);
	}
	if (error < 0) {
		kfree(p);
		return error;
	}

	if (p) {
		driver->ttys = (struct tty_struct **)p;
		driver->termios = (struct ktermios **)(p + driver->num);
	} else {
		driver->ttys = NULL;
		driver->termios = NULL;
	}

	cdev_init(&driver->cdev, &tty_fops);
	driver->cdev.owner = driver->owner;
	error = cdev_add(&driver->cdev, dev, driver->num);
	if (error) {
		unregister_chrdev_region(dev, driver->num);
		driver->ttys = NULL;
		driver->termios = NULL;
		kfree(p);
		return error;
	}

	mutex_lock(&tty_mutex);
	list_add(&driver->tty_drivers, &tty_drivers);
	mutex_unlock(&tty_mutex);

	if (!(driver->flags & TTY_DRIVER_DYNAMIC_DEV)) {
		for (i = 0; i < driver->num; i++)
		    tty_register_device(driver, i, NULL);
	}
	proc_tty_register_driver(driver);
	driver->flags |= TTY_DRIVER_INSTALLED;
	return 0;
}