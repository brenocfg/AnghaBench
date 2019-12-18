#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {int id; scalar_t__ value; } ;
struct camera_data {int dummy; } ;
struct TYPE_8__ {int id; scalar_t__ minimum; scalar_t__ maximum; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {scalar_t__ value; } ;

/* Variables and functions */
#define  CPIA2_CID_FLICKER_MODE 139 
#define  CPIA2_CID_FRAMERATE 138 
#define  CPIA2_CID_GPIO 137 
#define  CPIA2_CID_LIGHTS 136 
#define  CPIA2_CID_RESET_CAMERA 135 
#define  CPIA2_CID_TARGET_KB 134 
#define  CPIA2_CID_USB_ALT 133 
 int /*<<< orphan*/  DBG (char*,int,scalar_t__) ; 
 int EINVAL ; 
 int NUM_CONTROLS ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_VFLIP 128 
 TYPE_4__* controls ; 
 int /*<<< orphan*/  cpia2_reset_camera (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_set_brightness (struct camera_data*,scalar_t__) ; 
 int /*<<< orphan*/  cpia2_set_contrast (struct camera_data*,scalar_t__) ; 
 int cpia2_set_flicker_mode (struct camera_data*,int /*<<< orphan*/ ) ; 
 int cpia2_set_fps (struct camera_data*,int /*<<< orphan*/ ) ; 
 int cpia2_set_gpio (struct camera_data*,scalar_t__) ; 
 int /*<<< orphan*/  cpia2_set_property_flip (struct camera_data*,scalar_t__) ; 
 int /*<<< orphan*/  cpia2_set_property_mirror (struct camera_data*,scalar_t__) ; 
 int /*<<< orphan*/  cpia2_set_saturation (struct camera_data*,scalar_t__) ; 
 int cpia2_set_target_kb (struct camera_data*,scalar_t__) ; 
 int cpia2_usb_change_streaming_alternate (struct camera_data*,size_t) ; 
 int /*<<< orphan*/  cpia2_usb_stream_pause (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_resume (struct camera_data*) ; 
 TYPE_3__* flicker_controls ; 
 TYPE_2__* framerate_controls ; 
 TYPE_1__* lights_controls ; 

__attribute__((used)) static int ioctl_s_ctrl(void *arg,struct camera_data *cam)
{
	struct v4l2_control *c = arg;
	int i;
	int retval = 0;

	DBG("Set control id:%d, value:%d\n", c->id, c->value);

	/* Check that the value is in range */
	for(i=0; i<NUM_CONTROLS; i++) {
		if(c->id == controls[i].id) {
			if(c->value < controls[i].minimum ||
			   c->value > controls[i].maximum) {
				return -EINVAL;
			}
			break;
		}
	}
	if(i == NUM_CONTROLS)
		return -EINVAL;

	switch(c->id) {
	case V4L2_CID_BRIGHTNESS:
		cpia2_set_brightness(cam, c->value);
		break;
	case V4L2_CID_CONTRAST:
		cpia2_set_contrast(cam, c->value);
		break;
	case V4L2_CID_SATURATION:
		cpia2_set_saturation(cam, c->value);
		break;
	case V4L2_CID_HFLIP:
		cpia2_set_property_mirror(cam, c->value);
		break;
	case V4L2_CID_VFLIP:
		cpia2_set_property_flip(cam, c->value);
		break;
	case CPIA2_CID_TARGET_KB:
		retval = cpia2_set_target_kb(cam, c->value);
		break;
	case CPIA2_CID_GPIO:
		retval = cpia2_set_gpio(cam, c->value);
		break;
	case CPIA2_CID_FLICKER_MODE:
		retval = cpia2_set_flicker_mode(cam,
					      flicker_controls[c->value].value);
		break;
	case CPIA2_CID_FRAMERATE:
		retval = cpia2_set_fps(cam, framerate_controls[c->value].value);
		break;
	case CPIA2_CID_USB_ALT:
		retval = cpia2_usb_change_streaming_alternate(cam, c->value);
		break;
	case CPIA2_CID_LIGHTS:
		retval = cpia2_set_gpio(cam, lights_controls[c->value].value);
		break;
	case CPIA2_CID_RESET_CAMERA:
		cpia2_usb_stream_pause(cam);
		cpia2_reset_camera(cam);
		cpia2_usb_stream_resume(cam);
		break;
	default:
		retval = -EINVAL;
	}

	return retval;
}