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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct si4713_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  frequency; scalar_t__ power_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si4713_to_v4l2 (int /*<<< orphan*/ ) ; 
 int si4713_tx_tune_status (struct si4713_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_g_frequency(struct v4l2_subdev *sd, struct v4l2_frequency *f)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	int rval = 0;

	f->type = V4L2_TUNER_RADIO;

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		u16 freq;
		u8 p, a, n;

		rval = si4713_tx_tune_status(sdev, 0x00, &freq, &p, &a, &n);
		if (rval < 0)
			goto unlock;

		sdev->frequency = freq;
	}

	f->frequency = si4713_to_v4l2(sdev->frequency);

unlock:
	mutex_unlock(&sdev->mutex);
	return rval;
}