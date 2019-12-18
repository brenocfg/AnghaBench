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
struct video_device {int dummy; } ;
struct file {struct cpia2_fh* private_data; } ;
struct cpia2_fh {int open_count; scalar_t__ prio; int /*<<< orphan*/  busy_lock; scalar_t__ present; scalar_t__ mmapped; } ;
struct camera_data {int open_count; scalar_t__ prio; int /*<<< orphan*/  busy_lock; scalar_t__ present; scalar_t__ mmapped; } ;

/* Variables and functions */
 scalar_t__ V4L2_PRIORITY_RECORD ; 
 int /*<<< orphan*/  cpia2_free_buffers (struct cpia2_fh*) ; 
 int /*<<< orphan*/  cpia2_save_camera_state (struct cpia2_fh*) ; 
 int /*<<< orphan*/  cpia2_set_low_power (struct cpia2_fh*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_stop (struct cpia2_fh*) ; 
 int /*<<< orphan*/  kfree (struct cpia2_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_close (scalar_t__*,scalar_t__*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct cpia2_fh* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int cpia2_close(struct file *file)
{
	struct video_device *dev = video_devdata(file);
	struct camera_data *cam = video_get_drvdata(dev);
	struct cpia2_fh *fh = file->private_data;

	mutex_lock(&cam->busy_lock);

	if (cam->present &&
	    (cam->open_count == 1
	     || fh->prio == V4L2_PRIORITY_RECORD
	    )) {
		cpia2_usb_stream_stop(cam);

		if(cam->open_count == 1) {
			/* save camera state for later open */
			cpia2_save_camera_state(cam);

			cpia2_set_low_power(cam);
			cpia2_free_buffers(cam);
		}
	}

	{
		if(fh->mmapped)
			cam->mmapped = 0;
		v4l2_prio_close(&cam->prio,&fh->prio);
		file->private_data = NULL;
		kfree(fh);
	}

	if (--cam->open_count == 0) {
		cpia2_free_buffers(cam);
		if (!cam->present) {
			video_unregister_device(dev);
			mutex_unlock(&cam->busy_lock);
			kfree(cam);
			return 0;
		}
	}

	mutex_unlock(&cam->busy_lock);

	return 0;
}