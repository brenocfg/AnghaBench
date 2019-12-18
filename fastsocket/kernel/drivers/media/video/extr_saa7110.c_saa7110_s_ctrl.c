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
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct saa7110 {int /*<<< orphan*/  hue; int /*<<< orphan*/  sat; int /*<<< orphan*/  contrast; int /*<<< orphan*/  bright; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  saa7110_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 struct saa7110* to_saa7110 (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7110_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct saa7110 *decoder = to_saa7110(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		if (decoder->bright != ctrl->value) {
			decoder->bright = ctrl->value;
			saa7110_write(sd, 0x19, decoder->bright);
		}
		break;
	case V4L2_CID_CONTRAST:
		if (decoder->contrast != ctrl->value) {
			decoder->contrast = ctrl->value;
			saa7110_write(sd, 0x13, decoder->contrast);
		}
		break;
	case V4L2_CID_SATURATION:
		if (decoder->sat != ctrl->value) {
			decoder->sat = ctrl->value;
			saa7110_write(sd, 0x12, decoder->sat);
		}
		break;
	case V4L2_CID_HUE:
		if (decoder->hue != ctrl->value) {
			decoder->hue = ctrl->value;
			saa7110_write(sd, 0x07, decoder->hue);
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}