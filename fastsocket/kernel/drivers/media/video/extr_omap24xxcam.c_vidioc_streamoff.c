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
struct videobuf_queue {int dummy; } ;
struct omap24xxcam_fh {struct videobuf_queue vbq; struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {int /*<<< orphan*/  reset_disable; TYPE_1__* dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * streaming; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int videobuf_streamoff (struct videobuf_queue*) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *fh, enum v4l2_buf_type i)
{
	struct omap24xxcam_fh *ofh = fh;
	struct omap24xxcam_device *cam = ofh->cam;
	struct videobuf_queue *q = &ofh->vbq;
	int rval;

	atomic_inc(&cam->reset_disable);

	flush_scheduled_work();

	rval = videobuf_streamoff(q);
	if (!rval) {
		mutex_lock(&cam->mutex);
		cam->streaming = NULL;
		mutex_unlock(&cam->mutex);
		sysfs_notify(&cam->dev->kobj, NULL, "streaming");
	}

	atomic_dec(&cam->reset_disable);

	return rval;
}