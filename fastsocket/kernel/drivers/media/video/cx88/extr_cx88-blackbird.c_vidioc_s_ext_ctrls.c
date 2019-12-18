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
struct cx8802_fh {struct cx8802_dev* dev; } ;
struct cx2341x_mpeg_params {int dummy; } ;
struct cx8802_dev {struct cx2341x_mpeg_params params; scalar_t__ mpeg_active; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 int /*<<< orphan*/  VIDIOC_S_EXT_CTRLS ; 
 int /*<<< orphan*/  blackbird_mbox_func ; 
 int /*<<< orphan*/  blackbird_stop_codec (struct cx8802_dev*) ; 
 int cx2341x_ext_ctrls (struct cx2341x_mpeg_params*,int /*<<< orphan*/ ,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 
 int cx2341x_update (struct cx8802_dev*,int /*<<< orphan*/ ,struct cx2341x_mpeg_params*,struct cx2341x_mpeg_params*) ; 

__attribute__((used)) static int vidioc_s_ext_ctrls (struct file *file, void *priv,
			       struct v4l2_ext_controls *f)
{
	struct cx8802_dev *dev  = ((struct cx8802_fh *)priv)->dev;
	struct cx2341x_mpeg_params p;
	int err;

	if (f->ctrl_class != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;

	if (dev->mpeg_active)
		blackbird_stop_codec(dev);

	p = dev->params;
	err = cx2341x_ext_ctrls(&p, 0, f, VIDIOC_S_EXT_CTRLS);
	if (!err) {
		err = cx2341x_update(dev, blackbird_mbox_func, &dev->params, &p);
		dev->params = p;
	}
	return err;
}