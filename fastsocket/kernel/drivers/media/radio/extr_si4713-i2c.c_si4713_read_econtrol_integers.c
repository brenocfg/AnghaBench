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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_ext_control {scalar_t__ id; int value; } ;
struct si4713_device {int /*<<< orphan*/  mutex; scalar_t__ power_state; } ;
typedef  scalar_t__ s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ V4L2_CID_AUDIO_COMPRESSION_THRESHOLD ; 
 int dev_to_usecs (int,unsigned long*,int) ; 
 int get_status_bit (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ si4713_choose_econtrol_action (struct si4713_device*,scalar_t__,int**,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int*,unsigned long**,int*) ; 
 scalar_t__ si4713_read_property (struct si4713_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int si4713_read_econtrol_integers(struct si4713_device *sdev,
				struct v4l2_ext_control *control)
{
	s32 rval;
	u32 *shadow = NULL, val = 0;
	s32 bit = 0, mask = 0;
	u16 property = 0;
	int mul = 0;
	unsigned long *table = NULL;
	int size = 0;

	rval = si4713_choose_econtrol_action(sdev, control->id, &shadow, &bit,
			&mask, &property, &mul, &table, &size);
	if (rval < 0)
		goto exit;

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		rval = si4713_read_property(sdev, property, &val);
		if (rval < 0)
			goto unlock;

		/* Keep negative values for threshold */
		if (control->id == V4L2_CID_AUDIO_COMPRESSION_THRESHOLD)
			*shadow = (s16)val;
		else if (mask)
			*shadow = get_status_bit(val, bit, mask);
		else if (mul)
			*shadow = val * mul;
		else
			*shadow = dev_to_usecs(val, table, size);
	}

	control->value = *shadow;

unlock:
	mutex_unlock(&sdev->mutex);
exit:
	return rval;
}