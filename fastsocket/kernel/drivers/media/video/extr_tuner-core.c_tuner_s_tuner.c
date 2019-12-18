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
struct v4l2_tuner {int /*<<< orphan*/  audmode; int /*<<< orphan*/  type; } ;
struct v4l2_subdev {int dummy; } ;
struct tuner {scalar_t__ mode; int /*<<< orphan*/  audmode; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  set_mode_freq (struct i2c_client*,struct tuner*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tuner* to_tuner (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tuner_s_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct tuner *t = to_tuner(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (set_mode_freq(client, t, vt->type, 0) == -EINVAL)
		return 0;

	if (t->mode == V4L2_TUNER_RADIO)
		t->audmode = vt->audmode;

	return 0;
}