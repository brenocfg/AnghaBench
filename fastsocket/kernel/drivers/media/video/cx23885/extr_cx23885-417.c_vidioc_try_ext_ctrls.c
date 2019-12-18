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
struct v4l2_ext_controls {scalar_t__ ctrl_class; } ;
struct file {int dummy; } ;
struct cx23885_fh {struct cx23885_dev* dev; } ;
struct cx2341x_mpeg_params {int dummy; } ;
struct cx23885_dev {struct cx2341x_mpeg_params mpeg_params; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 int /*<<< orphan*/  VIDIOC_TRY_EXT_CTRLS ; 
 int cx2341x_ext_ctrls (struct cx2341x_mpeg_params*,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_try_ext_ctrls(struct file *file, void *priv,
				struct v4l2_ext_controls *f)
{
	struct cx23885_fh  *fh  = priv;
	struct cx23885_dev *dev = fh->dev;
	struct cx2341x_mpeg_params p;
	int err;

	if (f->ctrl_class != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;

	p = dev->mpeg_params;
	err = cx2341x_ext_ctrls(&p, 0, f, VIDIOC_TRY_EXT_CTRLS);
	return err;
}