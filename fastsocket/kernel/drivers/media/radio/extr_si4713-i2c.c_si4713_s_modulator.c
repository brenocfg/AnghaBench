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
typedef  void* u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_modulator {scalar_t__ index; int txsubchans; } ;
struct TYPE_2__ {void* enabled; } ;
struct si4713_device {int /*<<< orphan*/  mutex; TYPE_1__ rds_info; void* stereo; scalar_t__ power_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SI4713_TX_COMPONENT_ENABLE ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_RDS ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bits (int /*<<< orphan*/ ,void*,int,int) ; 
 int si4713_read_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int si4713_write_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_s_modulator(struct v4l2_subdev *sd, struct v4l2_modulator *vm)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	int rval = 0;
	u16 stereo, rds;
	u32 p;

	if (!sdev)
		return -ENODEV;

	if (vm->index > 0)
		return -EINVAL;

	/* Set audio mode: mono or stereo */
	if (vm->txsubchans & V4L2_TUNER_SUB_STEREO)
		stereo = 1;
	else if (vm->txsubchans & V4L2_TUNER_SUB_MONO)
		stereo = 0;
	else
		return -EINVAL;

	rds = !!(vm->txsubchans & V4L2_TUNER_SUB_RDS);

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		rval = si4713_read_property(sdev,
						SI4713_TX_COMPONENT_ENABLE, &p);
		if (rval < 0)
			goto unlock;

		p = set_bits(p, stereo, 1, 1 << 1);
		p = set_bits(p, rds, 2, 1 << 2);

		rval = si4713_write_property(sdev,
						SI4713_TX_COMPONENT_ENABLE, p);
		if (rval < 0)
			goto unlock;
	}

	sdev->stereo = stereo;
	sdev->rds_info.enabled = rds;

unlock:
	mutex_unlock(&sdev->mutex);
	return rval;
}