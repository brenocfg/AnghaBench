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
struct v4l2_ext_control {int id; int /*<<< orphan*/  value; } ;
struct si4713_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  antenna_capacitor; int /*<<< orphan*/  power_level; scalar_t__ power_state; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
#define  V4L2_CID_TUNE_ANTENNA_CAPACITOR 129 
#define  V4L2_CID_TUNE_POWER_LEVEL 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ si4713_update_tune_status (struct si4713_device*) ; 

__attribute__((used)) static int si4713_read_econtrol_tune(struct si4713_device *sdev,
				struct v4l2_ext_control *control)
{
	s32 rval = 0;

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		rval = si4713_update_tune_status(sdev);
		if (rval < 0)
			goto unlock;
	}

	switch (control->id) {
	case V4L2_CID_TUNE_POWER_LEVEL:
		control->value = sdev->power_level;
		break;
	case V4L2_CID_TUNE_ANTENNA_CAPACITOR:
		control->value = sdev->antenna_capacitor;
		break;
	default:
		rval = -EINVAL;
	};

unlock:
	mutex_unlock(&sdev->mutex);
	return rval;
}