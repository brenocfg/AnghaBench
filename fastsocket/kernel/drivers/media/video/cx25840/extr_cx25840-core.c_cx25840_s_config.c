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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; int /*<<< orphan*/  pvr150_workaround; } ;
struct cx25840_platform_data {int /*<<< orphan*/  pvr150_workaround; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_input (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_s_config(struct v4l2_subdev *sd, int irq, void *platform_data)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (platform_data) {
		struct cx25840_platform_data *pdata = platform_data;

		state->pvr150_workaround = pdata->pvr150_workaround;
		set_input(client, state->vid_input, state->aud_input);
	}
	return 0;
}