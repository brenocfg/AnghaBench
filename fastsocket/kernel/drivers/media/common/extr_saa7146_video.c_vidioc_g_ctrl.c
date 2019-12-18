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
struct v4l2_queryctrl {int dummy; } ;
struct v4l2_control {int id; int value; } ;
struct saa7146_vv {int vflip; int hflip; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCS_CTRL ; 
 int /*<<< orphan*/  DEB_D (char*) ; 
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_VFLIP 128 
 struct v4l2_queryctrl* ctrl_by_id (int) ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *fh, struct v4l2_control *c)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct saa7146_vv *vv = dev->vv_data;
	const struct v4l2_queryctrl *ctrl;
	u32 value = 0;

	ctrl = ctrl_by_id(c->id);
	if (NULL == ctrl)
		return -EINVAL;
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		value = saa7146_read(dev, BCS_CTRL);
		c->value = 0xff & (value >> 24);
		DEB_D(("V4L2_CID_BRIGHTNESS: %d\n", c->value));
		break;
	case V4L2_CID_CONTRAST:
		value = saa7146_read(dev, BCS_CTRL);
		c->value = 0x7f & (value >> 16);
		DEB_D(("V4L2_CID_CONTRAST: %d\n", c->value));
		break;
	case V4L2_CID_SATURATION:
		value = saa7146_read(dev, BCS_CTRL);
		c->value = 0x7f & (value >> 0);
		DEB_D(("V4L2_CID_SATURATION: %d\n", c->value));
		break;
	case V4L2_CID_VFLIP:
		c->value = vv->vflip;
		DEB_D(("V4L2_CID_VFLIP: %d\n", c->value));
		break;
	case V4L2_CID_HFLIP:
		c->value = vv->hflip;
		DEB_D(("V4L2_CID_HFLIP: %d\n", c->value));
		break;
	default:
		return -EINVAL;
	}
	return 0;
}