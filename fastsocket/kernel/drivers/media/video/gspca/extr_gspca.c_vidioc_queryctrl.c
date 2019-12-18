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
typedef  int u32 ;
struct v4l2_queryctrl {int id; int /*<<< orphan*/  flags; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  default_value; } ;
struct TYPE_5__ {struct gspca_ctrl* ctrls; } ;
struct gspca_dev {int ctrl_dis; int ctrl_inac; TYPE_2__ cam; TYPE_1__* sd_desc; } ;
struct gspca_ctrl {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  def; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int id; } ;
struct ctrl {TYPE_3__ qctrl; } ;
struct TYPE_4__ {int nctrls; struct ctrl* ctrls; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_INACTIVE ; 
 int V4L2_CTRL_FLAG_NEXT_CTRL ; 
 int V4L2_CTRL_ID_MASK ; 
 int get_ctrl (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_queryctrl*,TYPE_3__*,int) ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *priv,
			   struct v4l2_queryctrl *q_ctrl)
{
	struct gspca_dev *gspca_dev = priv;
	const struct ctrl *ctrls;
	struct gspca_ctrl *gspca_ctrl;
	int i, idx;
	u32 id;

	id = q_ctrl->id;
	if (id & V4L2_CTRL_FLAG_NEXT_CTRL) {
		id &= V4L2_CTRL_ID_MASK;
		id++;
		idx = -1;
		for (i = 0; i < gspca_dev->sd_desc->nctrls; i++) {
			if (gspca_dev->ctrl_dis & (1 << i))
				continue;
			if (gspca_dev->sd_desc->ctrls[i].qctrl.id < id)
				continue;
			if (idx >= 0
			 && gspca_dev->sd_desc->ctrls[i].qctrl.id
				    > gspca_dev->sd_desc->ctrls[idx].qctrl.id)
				continue;
			idx = i;
		}
	} else {
		idx = get_ctrl(gspca_dev, id);
	}
	if (idx < 0)
		return -EINVAL;
	ctrls = &gspca_dev->sd_desc->ctrls[idx];
	memcpy(q_ctrl, &ctrls->qctrl, sizeof *q_ctrl);
	if (gspca_dev->cam.ctrls != NULL) {
		gspca_ctrl = &gspca_dev->cam.ctrls[idx];
		q_ctrl->default_value = gspca_ctrl->def;
		q_ctrl->minimum = gspca_ctrl->min;
		q_ctrl->maximum = gspca_ctrl->max;
	}
	if (gspca_dev->ctrl_inac & (1 << idx))
		q_ctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
	return 0;
}