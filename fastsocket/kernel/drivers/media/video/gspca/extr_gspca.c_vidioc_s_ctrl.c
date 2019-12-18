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
struct v4l2_control {scalar_t__ value; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {struct gspca_ctrl* ctrls; } ;
struct gspca_dev {int ctrl_inac; int usb_err; int /*<<< orphan*/  usb_lock; scalar_t__ streaming; int /*<<< orphan*/  present; TYPE_2__ cam; TYPE_1__* sd_desc; } ;
struct gspca_ctrl {scalar_t__ min; scalar_t__ max; scalar_t__ val; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ minimum; scalar_t__ maximum; } ;
struct ctrl {int (* set ) (struct gspca_dev*,scalar_t__) ;int /*<<< orphan*/  (* set_control ) (struct gspca_dev*) ;TYPE_3__ qctrl; } ;
struct TYPE_4__ {struct ctrl* ctrls; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int EINVAL ; 
 int ENODEV ; 
 int ERANGE ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int get_ctrl (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct gspca_dev*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct gspca_dev*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *priv,
			 struct v4l2_control *ctrl)
{
	struct gspca_dev *gspca_dev = priv;
	const struct ctrl *ctrls;
	struct gspca_ctrl *gspca_ctrl;
	int idx, ret;

	idx = get_ctrl(gspca_dev, ctrl->id);
	if (idx < 0)
		return -EINVAL;
	if (gspca_dev->ctrl_inac & (1 << idx))
		return -EINVAL;
	ctrls = &gspca_dev->sd_desc->ctrls[idx];
	if (gspca_dev->cam.ctrls != NULL) {
		gspca_ctrl = &gspca_dev->cam.ctrls[idx];
		if (ctrl->value < gspca_ctrl->min
		    || ctrl->value > gspca_ctrl->max)
			return -ERANGE;
	} else {
		gspca_ctrl = NULL;
		if (ctrl->value < ctrls->qctrl.minimum
		    || ctrl->value > ctrls->qctrl.maximum)
			return -ERANGE;
	}
	PDEBUG(D_CONF, "set ctrl [%08x] = %d", ctrl->id, ctrl->value);
	if (mutex_lock_interruptible(&gspca_dev->usb_lock))
		return -ERESTARTSYS;
	if (!gspca_dev->present) {
		ret = -ENODEV;
		goto out;
	}
	gspca_dev->usb_err = 0;
	if (ctrls->set != NULL) {
		ret = ctrls->set(gspca_dev, ctrl->value);
		goto out;
	}
	if (gspca_ctrl != NULL) {
		gspca_ctrl->val = ctrl->value;
		if (ctrls->set_control != NULL
		 && gspca_dev->streaming)
			ctrls->set_control(gspca_dev);
	}
	ret = gspca_dev->usb_err;
out:
	mutex_unlock(&gspca_dev->usb_lock);
	return ret;
}