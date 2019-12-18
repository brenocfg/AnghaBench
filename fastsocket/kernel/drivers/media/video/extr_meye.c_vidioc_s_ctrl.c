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
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAAGC ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERABRIGHTNESS ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERACOLOR ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERACONTRAST ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAHUE ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERAPICTURE ; 
 int /*<<< orphan*/  SONY_PIC_COMMAND_SETCAMERASHARPNESS ; 
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
 int /*<<< orphan*/  sony_pic_camera_command (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *fh, struct v4l2_control *c)
{
	mutex_lock(&meye.lock);
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERABRIGHTNESS, c->value);
		meye.picture.brightness = c->value << 10;
		break;
	case V4L2_CID_HUE:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAHUE, c->value);
		meye.picture.hue = c->value << 10;
		break;
	case V4L2_CID_CONTRAST:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERACONTRAST, c->value);
		meye.picture.contrast = c->value << 10;
		break;
	case V4L2_CID_SATURATION:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERACOLOR, c->value);
		meye.picture.colour = c->value << 10;
		break;
	case V4L2_CID_AGC:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAAGC, c->value);
		meye.params.agc = c->value;
		break;
	case V4L2_CID_SHARPNESS:
	case V4L2_CID_MEYE_SHARPNESS:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERASHARPNESS, c->value);
		meye.params.sharpness = c->value;
		break;
	case V4L2_CID_PICTURE:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAPICTURE, c->value);
		meye.params.picture = c->value;
		break;
	case V4L2_CID_JPEGQUAL:
		meye.params.quality = c->value;
		break;
	case V4L2_CID_FRAMERATE:
		meye.params.framerate = c->value;
		break;
	default:
		mutex_unlock(&meye.lock);
		return -EINVAL;
	}
	mutex_unlock(&meye.lock);

	return 0;
}