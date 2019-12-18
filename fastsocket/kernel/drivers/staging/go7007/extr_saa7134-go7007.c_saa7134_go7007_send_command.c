#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_queryctrl {int /*<<< orphan*/  id; } ;
struct v4l2_control {int /*<<< orphan*/  id; } ;
struct saa7134_go7007 {struct saa7134_dev* dev; } ;
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct go7007 {struct saa7134_go7007* hpi_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_CTRL_CLASS_USER ; 
 int /*<<< orphan*/  V4L2_CTRL_ID2CLASS (int /*<<< orphan*/ ) ; 
#define  VIDIOC_G_CTRL 132 
#define  VIDIOC_G_STD 131 
#define  VIDIOC_QUERYCTRL 130 
#define  VIDIOC_S_CTRL 129 
#define  VIDIOC_S_STD 128 
 int saa7134_g_ctrl_internal (struct saa7134_dev*,int /*<<< orphan*/ *,struct v4l2_control*) ; 
 int saa7134_queryctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct v4l2_queryctrl*) ; 
 int saa7134_s_ctrl_internal (struct saa7134_dev*,int /*<<< orphan*/ *,struct v4l2_control*) ; 
 int saa7134_s_std_internal (struct saa7134_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_go7007_send_command(struct go7007 *go, unsigned int cmd,
					void *arg)
{
	struct saa7134_go7007 *saa = go->hpi_context;
	struct saa7134_dev *dev = saa->dev;

	switch (cmd) {
	case VIDIOC_S_STD:
	{
		v4l2_std_id *std = arg;
		return saa7134_s_std_internal(dev, NULL, std);
	}
	case VIDIOC_G_STD:
	{
		v4l2_std_id *std = arg;
		*std = dev->tvnorm->id;
		return 0;
	}
	case VIDIOC_QUERYCTRL:
	{
		struct v4l2_queryctrl *ctrl = arg;
		if (V4L2_CTRL_ID2CLASS(ctrl->id) == V4L2_CTRL_CLASS_USER)
			return saa7134_queryctrl(NULL, NULL, ctrl);
	}
	case VIDIOC_G_CTRL:
	{
		struct v4l2_control *ctrl = arg;
		if (V4L2_CTRL_ID2CLASS(ctrl->id) == V4L2_CTRL_CLASS_USER)
			return saa7134_g_ctrl_internal(dev, NULL, ctrl);
	}
	case VIDIOC_S_CTRL:
	{
		struct v4l2_control *ctrl = arg;
		if (V4L2_CTRL_ID2CLASS(ctrl->id) == V4L2_CTRL_CLASS_USER)
			return saa7134_s_ctrl_internal(dev, NULL, ctrl);
	}
	}
	return -EINVAL;

}