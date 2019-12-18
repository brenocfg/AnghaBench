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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct cuse_conn {int /*<<< orphan*/  fc; TYPE_1__* cdev; scalar_t__ dev; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cuse_lock ; 
 int /*<<< orphan*/  device_unregister (scalar_t__) ; 
 struct cuse_conn* fc_to_cc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_conn_kill (int /*<<< orphan*/ *) ; 
 int fuse_dev_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cuse_channel_release(struct inode *inode, struct file *file)
{
	struct cuse_conn *cc = fc_to_cc(file->private_data);
	int rc;

	/* remove from the conntbl, no more access from this point on */
	spin_lock(&cuse_lock);
	list_del_init(&cc->list);
	spin_unlock(&cuse_lock);

	/* remove device */
	if (cc->dev)
		device_unregister(cc->dev);
	if (cc->cdev) {
		unregister_chrdev_region(cc->cdev->dev, 1);
		cdev_del(cc->cdev);
	}

	/* kill connection and shutdown channel */
	fuse_conn_kill(&cc->fc);
	rc = fuse_dev_release(inode, file);	/* puts the base reference */

	return rc;
}