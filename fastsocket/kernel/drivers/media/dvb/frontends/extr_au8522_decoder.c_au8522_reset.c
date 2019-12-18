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
struct au8522_state {scalar_t__ current_frequency; int /*<<< orphan*/  operational_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_ANALOG_MODE ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int,int) ; 
 struct au8522_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int au8522_reset(struct v4l2_subdev *sd, u32 val)
{
	struct au8522_state *state = to_state(sd);

	state->operational_mode = AU8522_ANALOG_MODE;

	/* Clear out any state associated with the digital side of the
	   chip, so that when it gets powered back up it won't think
	   that it is already tuned */
	state->current_frequency = 0;

	au8522_writereg(state, 0xa4, 1 << 5);

	return 0;
}