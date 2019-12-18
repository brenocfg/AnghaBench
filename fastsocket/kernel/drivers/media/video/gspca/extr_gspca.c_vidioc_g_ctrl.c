#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__* ctrls; } ;
struct gspca_dev {int /*<<< orphan*/  usb_lock; TYPE_3__ cam; scalar_t__ usb_err; int /*<<< orphan*/  present; TYPE_1__* sd_desc; } ;
struct file {int dummy; } ;
struct ctrl {int (* get ) (struct gspca_dev*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_4__ {struct ctrl* ctrls; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int get_ctrl (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct gspca_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *priv,
			 struct v4l2_control *ctrl)
{
	struct gspca_dev *gspca_dev = priv;
	const struct ctrl *ctrls;
	int idx, ret;

	idx = get_ctrl(gspca_dev, ctrl->id);
	if (idx < 0)
		return -EINVAL;
	ctrls = &gspca_dev->sd_desc->ctrls[idx];

	if (mutex_lock_interruptible(&gspca_dev->usb_lock))
		return -ERESTARTSYS;
	if (!gspca_dev->present) {
		ret = -ENODEV;
		goto out;
	}
	gspca_dev->usb_err = 0;
	if (ctrls->get != NULL) {
		ret = ctrls->get(gspca_dev, &ctrl->value);
		goto out;
	}
	if (gspca_dev->cam.ctrls != NULL)
		ctrl->value = gspca_dev->cam.ctrls[idx].val;
	ret = 0;
out:
	mutex_unlock(&gspca_dev->usb_lock);
	return ret;
}