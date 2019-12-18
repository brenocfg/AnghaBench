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
struct v4l2_streamparm {int /*<<< orphan*/  type; } ;
struct omap24xxcam_fh {struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sdev; scalar_t__ streaming; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap24xxcam_sensor_if_enable (struct omap24xxcam_device*) ; 
 int vidioc_int_g_parm (int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int vidioc_int_s_parm (int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 

__attribute__((used)) static int vidioc_s_parm(struct file *file, void *fh,
			 struct v4l2_streamparm *a)
{
	struct omap24xxcam_fh *ofh = fh;
	struct omap24xxcam_device *cam = ofh->cam;
	struct v4l2_streamparm old_streamparm;
	int rval;

	mutex_lock(&cam->mutex);
	if (cam->streaming) {
		rval = -EBUSY;
		goto out;
	}

	old_streamparm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	rval = vidioc_int_g_parm(cam->sdev, &old_streamparm);
	if (rval)
		goto out;

	rval = vidioc_int_s_parm(cam->sdev, a);
	if (rval)
		goto out;

	rval = omap24xxcam_sensor_if_enable(cam);
	/*
	 * Revert to old streaming parameters if enabling sensor
	 * interface with the new ones failed.
	 */
	if (rval)
		vidioc_int_s_parm(cam->sdev, &old_streamparm);

out:
	mutex_unlock(&cam->mutex);

	return rval;
}