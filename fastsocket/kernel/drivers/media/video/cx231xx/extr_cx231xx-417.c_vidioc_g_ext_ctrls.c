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
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int /*<<< orphan*/  mpeg_params; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 int /*<<< orphan*/  VIDIOC_G_EXT_CTRLS ; 
 int cx2341x_ext_ctrls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int vidioc_g_ext_ctrls(struct file *file, void *priv,
				struct v4l2_ext_controls *f)
{
	struct cx231xx_fh  *fh  = priv;
	struct cx231xx *dev = fh->dev;
	dprintk(3, "enter vidioc_g_ext_ctrls()\n");
	if (f->ctrl_class != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;
	dprintk(3, "exit vidioc_g_ext_ctrls()\n");
	return cx2341x_ext_ctrls(&dev->mpeg_params, 0, f, VIDIOC_G_EXT_CTRLS);
}