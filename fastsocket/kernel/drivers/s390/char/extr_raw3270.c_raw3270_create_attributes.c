#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct raw3270 {TYPE_1__* cdev; int /*<<< orphan*/  minor; void* cltubdev; void* clttydev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBM_FS3270_MAJOR ; 
 int /*<<< orphan*/  IBM_TTY3270_MAJOR ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  class3270 ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 void* device_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raw3270_create_attributes(struct raw3270 *rp)
{
	int rc;

	rc = sysfs_create_group(&rp->cdev->dev.kobj, &raw3270_attr_group);
	if (rc)
		goto out;

	rp->clttydev = device_create(class3270, &rp->cdev->dev,
				     MKDEV(IBM_TTY3270_MAJOR, rp->minor), NULL,
				     "tty%s", dev_name(&rp->cdev->dev));
	if (IS_ERR(rp->clttydev)) {
		rc = PTR_ERR(rp->clttydev);
		goto out_ttydev;
	}

	rp->cltubdev = device_create(class3270, &rp->cdev->dev,
				     MKDEV(IBM_FS3270_MAJOR, rp->minor), NULL,
				     "tub%s", dev_name(&rp->cdev->dev));
	if (!IS_ERR(rp->cltubdev))
		goto out;

	rc = PTR_ERR(rp->cltubdev);
	device_destroy(class3270, MKDEV(IBM_TTY3270_MAJOR, rp->minor));

out_ttydev:
	sysfs_remove_group(&rp->cdev->dev.kobj, &raw3270_attr_group);
out:
	return rc;
}