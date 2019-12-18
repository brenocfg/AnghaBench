#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap24xxcam_fh {int /*<<< orphan*/  vbq; struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {TYPE_2__* sdev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  users; int /*<<< orphan*/  reset_disable; TYPE_1__* dev; struct file* streaming; } ;
struct file {struct omap24xxcam_fh* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  module; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kfree (struct omap24xxcam_fh*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_poweron_reset (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_disable (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_vbq_free_mmap_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  videobuf_streamoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap24xxcam_release(struct file *file)
{
	struct omap24xxcam_fh *fh = file->private_data;
	struct omap24xxcam_device *cam = fh->cam;

	atomic_inc(&cam->reset_disable);

	flush_scheduled_work();

	/* stop streaming capture */
	videobuf_streamoff(&fh->vbq);

	mutex_lock(&cam->mutex);
	if (cam->streaming == file) {
		cam->streaming = NULL;
		mutex_unlock(&cam->mutex);
		sysfs_notify(&cam->dev->kobj, NULL, "streaming");
	} else {
		mutex_unlock(&cam->mutex);
	}

	atomic_dec(&cam->reset_disable);

	omap24xxcam_vbq_free_mmap_buffers(&fh->vbq);

	/*
	 * Make sure the reset work we might have scheduled is not
	 * pending! It may be run *only* if we have users. (And it may
	 * not be scheduled anymore since streaming is already
	 * disabled.)
	 */
	flush_scheduled_work();

	mutex_lock(&cam->mutex);
	if (atomic_dec_return(&cam->users) == 0) {
		omap24xxcam_sensor_disable(cam);
		omap24xxcam_poweron_reset(cam);
	}
	mutex_unlock(&cam->mutex);

	file->private_data = NULL;

	module_put(cam->sdev->module);
	kfree(fh);

	return 0;
}