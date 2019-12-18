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
struct v4l2_control {scalar_t__ id; int /*<<< orphan*/  value; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {TYPE_2__* ext_vv_data; scalar_t__ ext_priv; } ;
struct hexium {int /*<<< orphan*/  cur_bw; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__* core_ops; } ;
struct TYPE_4__ {int (* vidioc_g_ctrl ) (struct file*,void*,struct v4l2_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int EINVAL ; 
 int HEXIUM_CONTROLS ; 
 scalar_t__ V4L2_CID_PRIVATE_BASE ; 
 TYPE_3__* hexium_controls ; 
 int stub1 (struct file*,void*,struct v4l2_control*) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *fh, struct v4l2_control *vc)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct hexium *hexium = (struct hexium *) dev->ext_priv;
	int i;

	for (i = HEXIUM_CONTROLS - 1; i >= 0; i--) {
		if (hexium_controls[i].id == vc->id)
			break;
	}

	if (i < 0)
		return dev->ext_vv_data->core_ops->vidioc_g_ctrl(file, fh, vc);

	if (vc->id == V4L2_CID_PRIVATE_BASE) {
		vc->value = hexium->cur_bw;
		DEB_D(("VIDIOC_G_CTRL BW:%d.\n", vc->value));
		return 0;
	}
	return -EINVAL;
}