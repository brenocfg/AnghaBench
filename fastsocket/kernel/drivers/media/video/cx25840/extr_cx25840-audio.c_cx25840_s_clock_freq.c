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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {scalar_t__ aud_input; } ;

/* Variables and functions */
 scalar_t__ CX25840_AUDIO_SERIAL ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  is_cx2583x (struct cx25840_state*) ; 
 int set_audclk_freq (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx25840_s_clock_freq(struct v4l2_subdev *sd, u32 freq)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct cx25840_state *state = to_state(sd);
	int retval;

	if (!is_cx2583x(state))
		cx25840_and_or(client, 0x810, ~0x1, 1);
	if (state->aud_input != CX25840_AUDIO_SERIAL) {
		cx25840_and_or(client, 0x803, ~0x10, 0);
		cx25840_write(client, 0x8d3, 0x1f);
	}
	retval = set_audclk_freq(client, freq);
	if (state->aud_input != CX25840_AUDIO_SERIAL)
		cx25840_and_or(client, 0x803, ~0x10, 0x10);
	if (!is_cx2583x(state))
		cx25840_and_or(client, 0x810, ~0x1, 0);
	return retval;
}