#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ext_control {int id; int /*<<< orphan*/  string; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  radio_text; int /*<<< orphan*/  ps_name; } ;
struct si4713_device {TYPE_1__ rds_info; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MAX_RDS_PS_NAME ; 
 int /*<<< orphan*/  MAX_RDS_RADIO_TEXT ; 
#define  V4L2_CID_RDS_TX_PS_NAME 129 
#define  V4L2_CID_RDS_TX_RADIO_TEXT 128 
 int copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_read_econtrol_string(struct si4713_device *sdev,
				struct v4l2_ext_control *control)
{
	s32 rval = 0;

	switch (control->id) {
	case V4L2_CID_RDS_TX_PS_NAME:
		if (strlen(sdev->rds_info.ps_name) + 1 > control->size) {
			control->size = MAX_RDS_PS_NAME + 1;
			rval = -ENOSPC;
			goto exit;
		}
		rval = copy_to_user(control->string, sdev->rds_info.ps_name,
					strlen(sdev->rds_info.ps_name) + 1);
		break;

	case V4L2_CID_RDS_TX_RADIO_TEXT:
		if (strlen(sdev->rds_info.radio_text) + 1 > control->size) {
			control->size = MAX_RDS_RADIO_TEXT + 1;
			rval = -ENOSPC;
			goto exit;
		}
		rval = copy_to_user(control->string, sdev->rds_info.radio_text,
					strlen(sdev->rds_info.radio_text) + 1);
		break;

	default:
		rval = -EINVAL;
		break;
	};

exit:
	return rval;
}