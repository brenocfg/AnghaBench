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
struct v4l2_ext_control {int value; int /*<<< orphan*/  id; } ;
struct si4713_device {int /*<<< orphan*/  mutex; scalar_t__ power_state; int /*<<< orphan*/  sd; } ;
typedef  int s32 ;

/* Variables and functions */
 int dev_to_usecs (int,unsigned long*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_bits (int,int,int,int) ; 
 int si4713_choose_econtrol_action (struct si4713_device*,int /*<<< orphan*/ ,int**,int*,int*,int /*<<< orphan*/ *,int*,unsigned long**,int*) ; 
 int si4713_read_property (struct si4713_device*,int /*<<< orphan*/ ,int*) ; 
 int si4713_write_property (struct si4713_device*,int /*<<< orphan*/ ,int) ; 
 int usecs_to_dev (int,unsigned long*,int) ; 
 int validate_range (int /*<<< orphan*/ *,struct v4l2_ext_control*) ; 

__attribute__((used)) static int si4713_write_econtrol_integers(struct si4713_device *sdev,
					struct v4l2_ext_control *control)
{
	s32 rval;
	u32 *shadow = NULL, val = 0;
	s32 bit = 0, mask = 0;
	u16 property = 0;
	int mul = 0;
	unsigned long *table = NULL;
	int size = 0;

	rval = validate_range(&sdev->sd, control);
	if (rval < 0)
		goto exit;

	rval = si4713_choose_econtrol_action(sdev, control->id, &shadow, &bit,
			&mask, &property, &mul, &table, &size);
	if (rval < 0)
		goto exit;

	val = control->value;
	if (mul) {
		val = control->value / mul;
	} else if (table) {
		rval = usecs_to_dev(control->value, table, size);
		if (rval < 0)
			goto exit;
		val = rval;
		rval = 0;
	}

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		if (mask) {
			rval = si4713_read_property(sdev, property, &val);
			if (rval < 0)
				goto unlock;
			val = set_bits(val, control->value, bit, mask);
		}

		rval = si4713_write_property(sdev, property, val);
		if (rval < 0)
			goto unlock;
		if (mask)
			val = control->value;
	}

	if (mul) {
		*shadow = val * mul;
	} else if (table) {
		rval = dev_to_usecs(val, table, size);
		if (rval < 0)
			goto unlock;
		*shadow = rval;
		rval = 0;
	} else {
		*shadow = val;
	}

unlock:
	mutex_unlock(&sdev->mutex);
exit:
	return rval;
}