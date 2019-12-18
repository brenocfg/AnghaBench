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
struct saa7127_state {int reg_3a_cb; int reg_3a; int input_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SAA7127_INPUT_TYPE_NORMAL 129 
#define  SAA7127_INPUT_TYPE_TEST_IMAGE 128 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7127_write (struct v4l2_subdev*,int,int) ; 
 struct saa7127_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int saa7127_set_input_type(struct v4l2_subdev *sd, int input)
{
	struct saa7127_state *state = to_state(sd);

	switch (input) {
	case SAA7127_INPUT_TYPE_NORMAL:	/* avia */
		v4l2_dbg(1, debug, sd, "Selecting Normal Encoder Input\n");
		state->reg_3a_cb = 0;
		break;

	case SAA7127_INPUT_TYPE_TEST_IMAGE:	/* color bar */
		v4l2_dbg(1, debug, sd, "Selecting Color Bar generator\n");
		state->reg_3a_cb = 0x80;
		break;

	default:
		return -EINVAL;
	}
	saa7127_write(sd, 0x3a, state->reg_3a | state->reg_3a_cb);
	state->input_type = input;
	return 0;
}