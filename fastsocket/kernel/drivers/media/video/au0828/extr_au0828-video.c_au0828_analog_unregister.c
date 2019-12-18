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
struct au0828_dev {scalar_t__ vbi_dev; scalar_t__ vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_sysfs_lock ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (scalar_t__) ; 

void au0828_analog_unregister(struct au0828_dev *dev)
{
	dprintk(1, "au0828_release_resources called\n");
	mutex_lock(&au0828_sysfs_lock);

	if (dev->vdev)
		video_unregister_device(dev->vdev);
	if (dev->vbi_dev)
		video_unregister_device(dev->vbi_dev);

	mutex_unlock(&au0828_sysfs_lock);
}