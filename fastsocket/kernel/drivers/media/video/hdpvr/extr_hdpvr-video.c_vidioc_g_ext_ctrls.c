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
struct v4l2_ext_controls {scalar_t__ ctrl_class; int count; int error_idx; struct v4l2_ext_control* controls; } ;
struct v4l2_ext_control {int dummy; } ;
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct hdpvr_device {int /*<<< orphan*/  options; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 int hdpvr_get_ctrl (int /*<<< orphan*/ *,struct v4l2_ext_control*) ; 

__attribute__((used)) static int vidioc_g_ext_ctrls(struct file *file, void *priv,
			      struct v4l2_ext_controls *ctrls)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;
	int i, err = 0;

	if (ctrls->ctrl_class == V4L2_CTRL_CLASS_MPEG) {
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			err = hdpvr_get_ctrl(&dev->options, ctrl);
			if (err) {
				ctrls->error_idx = i;
				break;
			}
		}
		return err;

	}

	return -EINVAL;
}