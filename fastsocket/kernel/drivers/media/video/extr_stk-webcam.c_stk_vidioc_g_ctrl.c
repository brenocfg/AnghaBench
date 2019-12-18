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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct TYPE_2__ {int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  brightness; } ;
struct stk_camera {TYPE_1__ vsettings; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 130 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 

__attribute__((used)) static int stk_vidioc_g_ctrl(struct file *filp,
		void *priv, struct v4l2_control *c)
{
	struct stk_camera *dev = priv;
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		c->value = dev->vsettings.brightness;
		break;
	case V4L2_CID_HFLIP:
		c->value = dev->vsettings.hflip;
		break;
	case V4L2_CID_VFLIP:
		c->value = dev->vsettings.vflip;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}