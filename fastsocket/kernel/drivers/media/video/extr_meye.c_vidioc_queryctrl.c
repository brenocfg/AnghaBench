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
struct v4l2_queryctrl {int id; int maximum; int step; int default_value; int /*<<< orphan*/  flags; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; void* type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AGC 137 
#define  V4L2_CID_BRIGHTNESS 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_FRAMERATE 134 
#define  V4L2_CID_HUE 133 
#define  V4L2_CID_JPEGQUAL 132 
#define  V4L2_CID_MEYE_SHARPNESS 131 
#define  V4L2_CID_PICTURE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_DISABLED ; 
 void* V4L2_CTRL_TYPE_INTEGER ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_queryctrl(struct file *file, void *fh,
				struct v4l2_queryctrl *c)
{
	switch (c->id) {

	case V4L2_CID_BRIGHTNESS:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Brightness");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 32;
		c->flags = 0;
		break;
	case V4L2_CID_HUE:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Hue");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 32;
		c->flags = 0;
		break;
	case V4L2_CID_CONTRAST:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Contrast");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 32;
		c->flags = 0;
		break;
	case V4L2_CID_SATURATION:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Saturation");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 32;
		c->flags = 0;
		break;
	case V4L2_CID_AGC:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Agc");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 48;
		c->flags = 0;
		break;
	case V4L2_CID_MEYE_SHARPNESS:
	case V4L2_CID_SHARPNESS:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Sharpness");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 32;

		/* Continue to report legacy private SHARPNESS ctrl but
		 * say it is disabled in preference to ctrl in the spec
		 */
		c->flags = (c->id == V4L2_CID_SHARPNESS) ? 0 :
						V4L2_CTRL_FLAG_DISABLED;
		break;
	case V4L2_CID_PICTURE:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Picture");
		c->minimum = 0;
		c->maximum = 63;
		c->step = 1;
		c->default_value = 0;
		c->flags = 0;
		break;
	case V4L2_CID_JPEGQUAL:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "JPEG quality");
		c->minimum = 0;
		c->maximum = 10;
		c->step = 1;
		c->default_value = 8;
		c->flags = 0;
		break;
	case V4L2_CID_FRAMERATE:
		c->type = V4L2_CTRL_TYPE_INTEGER;
		strcpy(c->name, "Framerate");
		c->minimum = 0;
		c->maximum = 31;
		c->step = 1;
		c->default_value = 0;
		c->flags = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}