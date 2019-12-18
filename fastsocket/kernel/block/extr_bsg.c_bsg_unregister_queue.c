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
struct bsg_class_device {int /*<<< orphan*/  ref; int /*<<< orphan*/ * class_dev; int /*<<< orphan*/  minor; } ;
struct request_queue {int /*<<< orphan*/  kobj; struct bsg_class_device bsg_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsg_kref_release_function ; 
 int /*<<< orphan*/  bsg_minor_idr ; 
 int /*<<< orphan*/  bsg_mutex ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void bsg_unregister_queue(struct request_queue *q)
{
	struct bsg_class_device *bcd = &q->bsg_dev;

	if (!bcd->class_dev)
		return;

	mutex_lock(&bsg_mutex);
	idr_remove(&bsg_minor_idr, bcd->minor);
	sysfs_remove_link(&q->kobj, "bsg");
	device_unregister(bcd->class_dev);
	bcd->class_dev = NULL;
	kref_put(&bcd->ref, bsg_kref_release_function);
	mutex_unlock(&bsg_mutex);
}