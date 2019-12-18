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
struct fcoe_fcf_device {int dummy; } ;
struct fcoe_fcf {int /*<<< orphan*/ * fcf_dev; int /*<<< orphan*/  list; struct fcoe_ctlr* fip; } ;
struct fcoe_ctlr_device {int /*<<< orphan*/  lock; } ;
struct fcoe_ctlr {int /*<<< orphan*/  fcf_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct fcoe_ctlr_device* fcoe_ctlr_to_ctlr_dev (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  fcoe_fcf_device_delete (struct fcoe_fcf_device*) ; 
 struct fcoe_fcf_device* fcoe_fcf_to_fcf_dev (struct fcoe_fcf*) ; 
 int /*<<< orphan*/  kfree (struct fcoe_fcf*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fcoe_sysfs_fcf_del(struct fcoe_fcf *new)
{
	struct fcoe_ctlr *fip = new->fip;
	struct fcoe_ctlr_device *cdev;
	struct fcoe_fcf_device *fcf_dev;

	list_del(&new->list);
	fip->fcf_count--;

	/*
	 * If ctlr_dev doesn't exist then it means we're a libfcoe user
	 * who doesn't use fcoe_syfs and didn't allocate a fcoe_ctlr_device
	 * or a fcoe_fcf_device.
	 *
	 * fnic would be an example of a driver with this behavior. In this
	 * case we want to remove the fcoe_fcf from the fcoe_ctlr list (above),
	 * but we don't want to make sysfs changes.
	 */
	cdev = fcoe_ctlr_to_ctlr_dev(fip);
	if (cdev) {
		mutex_lock(&cdev->lock);
		fcf_dev = fcoe_fcf_to_fcf_dev(new);
		WARN_ON(!fcf_dev);
		new->fcf_dev = NULL;
		fcoe_fcf_device_delete(fcf_dev);
		kfree(new);
		mutex_unlock(&cdev->lock);
	}
}