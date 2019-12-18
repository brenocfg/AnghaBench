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
struct raw3270 {struct raw3270* ascebc; struct ccw_device* cdev; int /*<<< orphan*/  list; int /*<<< orphan*/  minor; scalar_t__ cltubdev; scalar_t__ clttydev; } ;
struct ccw_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBM_FS3270_MAJOR ; 
 int /*<<< orphan*/  IBM_TTY3270_MAJOR ; 
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class3270 ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct raw3270*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_mutex ; 

__attribute__((used)) static void
raw3270_delete_device(struct raw3270 *rp)
{
	struct ccw_device *cdev;

	/* Remove from device chain. */
	mutex_lock(&raw3270_mutex);
	if (rp->clttydev && !IS_ERR(rp->clttydev))
		device_destroy(class3270, MKDEV(IBM_TTY3270_MAJOR, rp->minor));
	if (rp->cltubdev && !IS_ERR(rp->cltubdev))
		device_destroy(class3270, MKDEV(IBM_FS3270_MAJOR, rp->minor));
	list_del_init(&rp->list);
	mutex_unlock(&raw3270_mutex);

	/* Disconnect from ccw_device. */
	cdev = rp->cdev;
	rp->cdev = NULL;
	dev_set_drvdata(&cdev->dev, NULL);
	cdev->handler = NULL;

	/* Put ccw_device structure. */
	put_device(&cdev->dev);

	/* Now free raw3270 structure. */
	kfree(rp->ascebc);
	kfree(rp);
}