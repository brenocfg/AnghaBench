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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct tuner {int /*<<< orphan*/  std; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  set_mode_freq (struct i2c_client*,struct tuner*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tuner* to_tuner (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tuner_fixup_std (struct tuner*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tuner_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct tuner *t = to_tuner(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (set_mode_freq(client, t, V4L2_TUNER_ANALOG_TV, 0) == -EINVAL)
		return 0;

	t->std = std;
	tuner_fixup_std(t);

	return 0;
}