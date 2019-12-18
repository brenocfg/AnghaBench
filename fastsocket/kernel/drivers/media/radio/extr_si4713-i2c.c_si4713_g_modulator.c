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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_modulator {scalar_t__ index; int capability; int /*<<< orphan*/  txsubchans; void* rangehigh; void* rangelow; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {void* enabled; } ;
struct si4713_device {int /*<<< orphan*/  mutex; TYPE_1__ rds_info; void* stereo; scalar_t__ power_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FREQ_RANGE_HIGH ; 
 int /*<<< orphan*/  FREQ_RANGE_LOW ; 
 int /*<<< orphan*/  SI4713_TX_COMPONENT_ENABLE ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_RDS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 void* get_status_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si4713_read_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* si4713_to_v4l2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_g_modulator(struct v4l2_subdev *sd, struct v4l2_modulator *vm)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	int rval = 0;

	if (!sdev) {
		rval = -ENODEV;
		goto exit;
	}

	if (vm->index > 0) {
		rval = -EINVAL;
		goto exit;
	}

	strncpy(vm->name, "FM Modulator", 32);
	vm->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LOW |
						V4L2_TUNER_CAP_RDS;

	/* Report current frequency range limits */
	vm->rangelow = si4713_to_v4l2(FREQ_RANGE_LOW);
	vm->rangehigh = si4713_to_v4l2(FREQ_RANGE_HIGH);

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		u32 comp_en = 0;

		rval = si4713_read_property(sdev, SI4713_TX_COMPONENT_ENABLE,
						&comp_en);
		if (rval < 0)
			goto unlock;

		sdev->stereo = get_status_bit(comp_en, 1, 1 << 1);
		sdev->rds_info.enabled = get_status_bit(comp_en, 2, 1 << 2);
	}

	/* Report current audio mode: mono or stereo */
	if (sdev->stereo)
		vm->txsubchans = V4L2_TUNER_SUB_STEREO;
	else
		vm->txsubchans = V4L2_TUNER_SUB_MONO;

	/* Report rds feature status */
	if (sdev->rds_info.enabled)
		vm->txsubchans |= V4L2_TUNER_SUB_RDS;
	else
		vm->txsubchans &= ~V4L2_TUNER_SUB_RDS;

unlock:
	mutex_unlock(&sdev->mutex);
exit:
	return rval;
}