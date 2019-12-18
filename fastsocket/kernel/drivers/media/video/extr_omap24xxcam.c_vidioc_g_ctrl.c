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
struct v4l2_control {int dummy; } ;
struct omap24xxcam_fh {struct omap24xxcam_device* cam; } ;
struct omap24xxcam_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vidioc_int_g_ctrl (int /*<<< orphan*/ ,struct v4l2_control*) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *fh,
			 struct v4l2_control *a)
{
	struct omap24xxcam_fh *ofh = fh;
	struct omap24xxcam_device *cam = ofh->cam;
	int rval;

	mutex_lock(&cam->mutex);
	rval = vidioc_int_g_ctrl(cam->sdev, a);
	mutex_unlock(&cam->mutex);

	return rval;
}