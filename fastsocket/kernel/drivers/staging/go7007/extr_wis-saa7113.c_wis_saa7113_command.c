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
typedef  int v4l2_std_id ;
struct wis_saa7113 {int norm; int brightness; int contrast; int saturation; int hue; } ;
struct v4l2_queryctrl {int minimum; int maximum; int step; int default_value; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; void* type; int /*<<< orphan*/  id; } ;
struct v4l2_control {int value; int /*<<< orphan*/  id; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
#define  V4L2_CID_BRIGHTNESS 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_HUE 134 
#define  V4L2_CID_SATURATION 133 
 void* V4L2_CTRL_TYPE_INTEGER ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
#define  VIDIOC_G_CTRL 132 
#define  VIDIOC_QUERYCTRL 131 
#define  VIDIOC_S_CTRL 130 
#define  VIDIOC_S_INPUT 129 
#define  VIDIOC_S_STD 128 
 struct wis_saa7113* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  write_reg (struct i2c_client*,int,int) ; 

__attribute__((used)) static int wis_saa7113_command(struct i2c_client *client,
				unsigned int cmd, void *arg)
{
	struct wis_saa7113 *dec = i2c_get_clientdata(client);

	switch (cmd) {
	case VIDIOC_S_INPUT:
	{
		int *input = arg;

		i2c_smbus_write_byte_data(client, 0x02, 0xC0 | *input);
		i2c_smbus_write_byte_data(client, 0x09,
				*input < 6 ? 0x40 : 0x80);
		break;
	}
	case VIDIOC_S_STD:
	{
		v4l2_std_id *input = arg;
		dec->norm = *input;
		if (dec->norm & V4L2_STD_NTSC) {
			write_reg(client, 0x0e, 0x01);
			write_reg(client, 0x10, 0x40);
		} else if (dec->norm & V4L2_STD_PAL) {
			write_reg(client, 0x0e, 0x01);
			write_reg(client, 0x10, 0x48);
		} else if (dec->norm * V4L2_STD_SECAM) {
			write_reg(client, 0x0e, 0x50);
			write_reg(client, 0x10, 0x48);
		}
		break;
	}
	case VIDIOC_QUERYCTRL:
	{
		struct v4l2_queryctrl *ctrl = arg;

		switch (ctrl->id) {
		case V4L2_CID_BRIGHTNESS:
			ctrl->type = V4L2_CTRL_TYPE_INTEGER;
			strncpy(ctrl->name, "Brightness", sizeof(ctrl->name));
			ctrl->minimum = 0;
			ctrl->maximum = 255;
			ctrl->step = 1;
			ctrl->default_value = 128;
			ctrl->flags = 0;
			break;
		case V4L2_CID_CONTRAST:
			ctrl->type = V4L2_CTRL_TYPE_INTEGER;
			strncpy(ctrl->name, "Contrast", sizeof(ctrl->name));
			ctrl->minimum = 0;
			ctrl->maximum = 127;
			ctrl->step = 1;
			ctrl->default_value = 71;
			ctrl->flags = 0;
			break;
		case V4L2_CID_SATURATION:
			ctrl->type = V4L2_CTRL_TYPE_INTEGER;
			strncpy(ctrl->name, "Saturation", sizeof(ctrl->name));
			ctrl->minimum = 0;
			ctrl->maximum = 127;
			ctrl->step = 1;
			ctrl->default_value = 64;
			ctrl->flags = 0;
			break;
		case V4L2_CID_HUE:
			ctrl->type = V4L2_CTRL_TYPE_INTEGER;
			strncpy(ctrl->name, "Hue", sizeof(ctrl->name));
			ctrl->minimum = -128;
			ctrl->maximum = 127;
			ctrl->step = 1;
			ctrl->default_value = 0;
			ctrl->flags = 0;
			break;
		}
		break;
	}
	case VIDIOC_S_CTRL:
	{
		struct v4l2_control *ctrl = arg;

		switch (ctrl->id) {
		case V4L2_CID_BRIGHTNESS:
			if (ctrl->value > 255)
				dec->brightness = 255;
			else if (ctrl->value < 0)
				dec->brightness = 0;
			else
				dec->brightness = ctrl->value;
			write_reg(client, 0x0a, dec->brightness);
			break;
		case V4L2_CID_CONTRAST:
			if (ctrl->value > 127)
				dec->contrast = 127;
			else if (ctrl->value < 0)
				dec->contrast = 0;
			else
				dec->contrast = ctrl->value;
			write_reg(client, 0x0b, dec->contrast);
			break;
		case V4L2_CID_SATURATION:
			if (ctrl->value > 127)
				dec->saturation = 127;
			else if (ctrl->value < 0)
				dec->saturation = 0;
			else
				dec->saturation = ctrl->value;
			write_reg(client, 0x0c, dec->saturation);
			break;
		case V4L2_CID_HUE:
			if (ctrl->value > 127)
				dec->hue = 127;
			else if (ctrl->value < -128)
				dec->hue = -128;
			else
				dec->hue = ctrl->value;
			write_reg(client, 0x0d, dec->hue);
			break;
		}
		break;
	}
	case VIDIOC_G_CTRL:
	{
		struct v4l2_control *ctrl = arg;

		switch (ctrl->id) {
		case V4L2_CID_BRIGHTNESS:
			ctrl->value = dec->brightness;
			break;
		case V4L2_CID_CONTRAST:
			ctrl->value = dec->contrast;
			break;
		case V4L2_CID_SATURATION:
			ctrl->value = dec->saturation;
			break;
		case V4L2_CID_HUE:
			ctrl->value = dec->hue;
			break;
		}
		break;
	}
	default:
		break;
	}
	return 0;
}