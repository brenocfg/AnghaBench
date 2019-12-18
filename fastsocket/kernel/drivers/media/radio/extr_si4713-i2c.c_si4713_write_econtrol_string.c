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
struct v4l2_queryctrl {int id; int step; } ;
struct v4l2_ext_control {int id; int /*<<< orphan*/  string; int /*<<< orphan*/  size; } ;
struct si4713_device {int /*<<< orphan*/  sd; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int MAX_RDS_PS_NAME ; 
 int MAX_RDS_RADIO_TEXT ; 
#define  V4L2_CID_RDS_TX_PS_NAME 129 
#define  V4L2_CID_RDS_TX_RADIO_TEXT 128 
 scalar_t__ copy_from_user (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ si4713_queryctrl (int /*<<< orphan*/ *,struct v4l2_queryctrl*) ; 
 scalar_t__ si4713_set_rds_ps_name (struct si4713_device*,char*) ; 
 scalar_t__ si4713_set_rds_radio_text (struct si4713_device*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int si4713_write_econtrol_string(struct si4713_device *sdev,
				struct v4l2_ext_control *control)
{
	struct v4l2_queryctrl vqc;
	int len;
	s32 rval = 0;

	vqc.id = control->id;
	rval = si4713_queryctrl(&sdev->sd, &vqc);
	if (rval < 0)
		goto exit;

	switch (control->id) {
	case V4L2_CID_RDS_TX_PS_NAME: {
		char ps_name[MAX_RDS_PS_NAME + 1];

		len = control->size - 1;
		if (len > MAX_RDS_PS_NAME) {
			rval = -ERANGE;
			goto exit;
		}
		rval = copy_from_user(ps_name, control->string, len);
		if (rval < 0)
			goto exit;
		ps_name[len] = '\0';

		if (strlen(ps_name) % vqc.step) {
			rval = -ERANGE;
			goto exit;
		}

		rval = si4713_set_rds_ps_name(sdev, ps_name);
	}
		break;

	case V4L2_CID_RDS_TX_RADIO_TEXT: {
		char radio_text[MAX_RDS_RADIO_TEXT + 1];

		len = control->size - 1;
		if (len > MAX_RDS_RADIO_TEXT) {
			rval = -ERANGE;
			goto exit;
		}
		rval = copy_from_user(radio_text, control->string, len);
		if (rval < 0)
			goto exit;
		radio_text[len] = '\0';

		if (strlen(radio_text) % vqc.step) {
			rval = -ERANGE;
			goto exit;
		}

		rval = si4713_set_rds_radio_text(sdev, radio_text);
	}
		break;

	default:
		rval = -EINVAL;
		break;
	};

exit:
	return rval;
}