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
struct v4l2_queryctrl {scalar_t__ id; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {TYPE_2__* ext_vv_data; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* core_ops; } ;
struct TYPE_3__ {int (* vidioc_queryctrl ) (struct file*,void*,struct v4l2_queryctrl*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int MAXCONTROLS ; 
 struct v4l2_queryctrl* mxb_controls ; 
 int stub1 (struct file*,void*,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *fh, struct v4l2_queryctrl *qc)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	int i;

	for (i = MAXCONTROLS - 1; i >= 0; i--) {
		if (mxb_controls[i].id == qc->id) {
			*qc = mxb_controls[i];
			DEB_D(("VIDIOC_QUERYCTRL %d.\n", qc->id));
			return 0;
		}
	}
	return dev->ext_vv_data->core_ops->vidioc_queryctrl(file, fh, qc);
}