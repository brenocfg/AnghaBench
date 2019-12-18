#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {int id; int value; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int agc; int sharpness; int picture; int quality; int framerate; } ;
struct TYPE_4__ {int brightness; int hue; int contrast; int colour; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__ params; TYPE_1__ picture; } ;

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
 TYPE_3__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *fh, struct v4l2_control *c)
{
	mutex_lock(&meye.lock);
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		c->value = meye.picture.brightness >> 10;
		break;
	case V4L2_CID_HUE:
		c->value = meye.picture.hue >> 10;
		break;
	case V4L2_CID_CONTRAST:
		c->value = meye.picture.contrast >> 10;
		break;
	case V4L2_CID_SATURATION:
		c->value = meye.picture.colour >> 10;
		break;
	case V4L2_CID_AGC:
		c->value = meye.params.agc;
		break;
	case V4L2_CID_SHARPNESS:
	case V4L2_CID_MEYE_SHARPNESS:
		c->value = meye.params.sharpness;
		break;
	case V4L2_CID_PICTURE:
		c->value = meye.params.picture;
		break;
	case V4L2_CID_JPEGQUAL:
		c->value = meye.params.quality;
		break;
	case V4L2_CID_FRAMERATE:
		c->value = meye.params.framerate;
		break;
	default:
		mutex_unlock(&meye.lock);
		return -EINVAL;
	}
	mutex_unlock(&meye.lock);

	return 0;
}