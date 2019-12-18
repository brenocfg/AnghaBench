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
struct v4l2_queryctrl {int dummy; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct saa7134_fh {int dummy; } ;
struct saa7134_dev {int /*<<< orphan*/  ctl_automute; int /*<<< orphan*/  ctl_y_odd; int /*<<< orphan*/  ctl_y_even; int /*<<< orphan*/  ctl_mirror; int /*<<< orphan*/  ctl_invert; int /*<<< orphan*/  ctl_volume; int /*<<< orphan*/  ctl_mute; int /*<<< orphan*/  ctl_saturation; int /*<<< orphan*/  ctl_contrast; int /*<<< orphan*/  ctl_hue; int /*<<< orphan*/  ctl_bright; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_MUTE 138 
#define  V4L2_CID_AUDIO_VOLUME 137 
#define  V4L2_CID_BRIGHTNESS 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_HFLIP 134 
#define  V4L2_CID_HUE 133 
#define  V4L2_CID_PRIVATE_AUTOMUTE 132 
#define  V4L2_CID_PRIVATE_INVERT 131 
#define  V4L2_CID_PRIVATE_Y_EVEN 130 
#define  V4L2_CID_PRIVATE_Y_ODD 129 
#define  V4L2_CID_SATURATION 128 
 struct v4l2_queryctrl* ctrl_by_id (int) ; 

int saa7134_g_ctrl_internal(struct saa7134_dev *dev, struct saa7134_fh *fh, struct v4l2_control *c)
{
	const struct v4l2_queryctrl* ctrl;

	ctrl = ctrl_by_id(c->id);
	if (NULL == ctrl)
		return -EINVAL;
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		c->value = dev->ctl_bright;
		break;
	case V4L2_CID_HUE:
		c->value = dev->ctl_hue;
		break;
	case V4L2_CID_CONTRAST:
		c->value = dev->ctl_contrast;
		break;
	case V4L2_CID_SATURATION:
		c->value = dev->ctl_saturation;
		break;
	case V4L2_CID_AUDIO_MUTE:
		c->value = dev->ctl_mute;
		break;
	case V4L2_CID_AUDIO_VOLUME:
		c->value = dev->ctl_volume;
		break;
	case V4L2_CID_PRIVATE_INVERT:
		c->value = dev->ctl_invert;
		break;
	case V4L2_CID_HFLIP:
		c->value = dev->ctl_mirror;
		break;
	case V4L2_CID_PRIVATE_Y_EVEN:
		c->value = dev->ctl_y_even;
		break;
	case V4L2_CID_PRIVATE_Y_ODD:
		c->value = dev->ctl_y_odd;
		break;
	case V4L2_CID_PRIVATE_AUTOMUTE:
		c->value = dev->ctl_automute;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}