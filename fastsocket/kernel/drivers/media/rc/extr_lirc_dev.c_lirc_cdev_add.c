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
struct lirc_driver {size_t minor; int /*<<< orphan*/  owner; int /*<<< orphan*/ * fops; } ;
struct irctl {struct lirc_driver d; } ;
struct cdev {int /*<<< orphan*/  kobj; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (struct cdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (struct cdev*,int /*<<< orphan*/ *) ; 
 struct cdev* cdevs ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int kobject_set_name (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lirc_base_dev ; 
 int /*<<< orphan*/  lirc_dev_fops ; 

__attribute__((used)) static int lirc_cdev_add(struct irctl *ir)
{
	int retval;
	struct lirc_driver *d = &ir->d;
	struct cdev *cdev = &cdevs[d->minor];

	if (d->fops) {
		cdev_init(cdev, d->fops);
		cdev->owner = d->owner;
	} else {
		cdev_init(cdev, &lirc_dev_fops);
		cdev->owner = THIS_MODULE;
	}
	retval = kobject_set_name(&cdev->kobj, "lirc%d", d->minor);
	if (retval)
		return retval;

	retval = cdev_add(cdev, MKDEV(MAJOR(lirc_base_dev), d->minor), 1);
	if (retval)
		kobject_put(&cdev->kobj);

	return retval;
}