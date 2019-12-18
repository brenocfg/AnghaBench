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
struct v4l2_tuner {int capability; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct msp_state {scalar_t__ opmode; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; scalar_t__ radio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ OPMODE_AUTOSELECT ; 
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  msp_detect_stereo (struct i2c_client*) ; 
 struct msp_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int msp_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct msp_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (state->radio)
		return 0;
	if (state->opmode == OPMODE_AUTOSELECT)
		msp_detect_stereo(client);
	vt->audmode    = state->audmode;
	vt->rxsubchans = state->rxsubchans;
	vt->capability |= V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	return 0;
}