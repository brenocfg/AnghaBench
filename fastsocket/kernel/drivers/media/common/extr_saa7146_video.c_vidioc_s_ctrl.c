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
typedef  int u32 ;
struct v4l2_queryctrl {int type; int minimum; int maximum; } ;
struct v4l2_control {int id; int value; } ;
struct saa7146_vv {int hflip; int vflip; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCS_CTRL ; 
 int /*<<< orphan*/  DEB_D (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_CAPTURE_ACTIVE (void*) ; 
 scalar_t__ IS_OVERLAY_ACTIVE (void*) ; 
 int MASK_06 ; 
 int MASK_22 ; 
 int /*<<< orphan*/  MC2 ; 
#define  V4L2_CID_BRIGHTNESS 135 
#define  V4L2_CID_CONTRAST 134 
#define  V4L2_CID_HFLIP 133 
#define  V4L2_CID_SATURATION 132 
#define  V4L2_CID_VFLIP 131 
#define  V4L2_CTRL_TYPE_BOOLEAN 130 
#define  V4L2_CTRL_TYPE_INTEGER 129 
#define  V4L2_CTRL_TYPE_MENU 128 
 struct v4l2_queryctrl* ctrl_by_id (int) ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_start_preview (void*) ; 
 int /*<<< orphan*/  saa7146_stop_preview (void*) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *fh, struct v4l2_control *c)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct saa7146_vv *vv = dev->vv_data;
	const struct v4l2_queryctrl *ctrl;

	ctrl = ctrl_by_id(c->id);
	if (NULL == ctrl) {
		DEB_D(("unknown control %d\n", c->id));
		return -EINVAL;
	}

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER:
		if (c->value < ctrl->minimum)
			c->value = ctrl->minimum;
		if (c->value > ctrl->maximum)
			c->value = ctrl->maximum;
		break;
	default:
		/* nothing */;
	}

	switch (c->id) {
	case V4L2_CID_BRIGHTNESS: {
		u32 value = saa7146_read(dev, BCS_CTRL);
		value &= 0x00ffffff;
		value |= (c->value << 24);
		saa7146_write(dev, BCS_CTRL, value);
		saa7146_write(dev, MC2, MASK_22 | MASK_06);
		break;
	}
	case V4L2_CID_CONTRAST: {
		u32 value = saa7146_read(dev, BCS_CTRL);
		value &= 0xff00ffff;
		value |= (c->value << 16);
		saa7146_write(dev, BCS_CTRL, value);
		saa7146_write(dev, MC2, MASK_22 | MASK_06);
		break;
	}
	case V4L2_CID_SATURATION: {
		u32 value = saa7146_read(dev, BCS_CTRL);
		value &= 0xffffff00;
		value |= (c->value << 0);
		saa7146_write(dev, BCS_CTRL, value);
		saa7146_write(dev, MC2, MASK_22 | MASK_06);
		break;
	}
	case V4L2_CID_HFLIP:
		/* fixme: we can support changing VFLIP and HFLIP here... */
		if (IS_CAPTURE_ACTIVE(fh) != 0) {
			DEB_D(("V4L2_CID_HFLIP while active capture.\n"));
			return -EBUSY;
		}
		vv->hflip = c->value;
		break;
	case V4L2_CID_VFLIP:
		if (IS_CAPTURE_ACTIVE(fh) != 0) {
			DEB_D(("V4L2_CID_VFLIP while active capture.\n"));
			return -EBUSY;
		}
		vv->vflip = c->value;
		break;
	default:
		return -EINVAL;
	}

	if (IS_OVERLAY_ACTIVE(fh) != 0) {
		saa7146_stop_preview(fh);
		saa7146_start_preview(fh);
	}
	return 0;
}