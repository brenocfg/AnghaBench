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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {scalar_t__ ident; scalar_t__ input; scalar_t__ output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R_02_INPUT_CNTL_1 ; 
 int /*<<< orphan*/  R_09_LUMA_CNTL ; 
 int /*<<< orphan*/  R_10_CHROMA_CNTL_2 ; 
 int /*<<< orphan*/  R_13_RT_X_PORT_OUT_CNTL ; 
 int /*<<< orphan*/  R_83_X_PORT_I_O_ENA_AND_OUT_CLK ; 
 scalar_t__ SAA7115_COMPOSITE4 ; 
 scalar_t__ SAA7115_COMPOSITE5 ; 
 scalar_t__ SAA7115_IPORT_ON ; 
 scalar_t__ SAA7115_SVIDEO0 ; 
 scalar_t__ SAA7115_SVIDEO3 ; 
 scalar_t__ V4L2_IDENT_SAA7111A ; 
 scalar_t__ V4L2_IDENT_SAA7113 ; 
 scalar_t__ V4L2_IDENT_SAA7114 ; 
 scalar_t__ V4L2_IDENT_SAA7115 ; 
 int /*<<< orphan*/  debug ; 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*,char*) ; 

__attribute__((used)) static int saa711x_s_routing(struct v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	struct saa711x_state *state = to_state(sd);
	u8 mask = (state->ident <= V4L2_IDENT_SAA7111A) ? 0xf8 : 0xf0;

	v4l2_dbg(1, debug, sd, "decoder set input %d output %d\n",
		input, output);

	/* saa7111/3 does not have these inputs */
	if (state->ident <= V4L2_IDENT_SAA7113 &&
	    (input == SAA7115_COMPOSITE4 ||
	     input == SAA7115_COMPOSITE5)) {
		return -EINVAL;
	}
	if (input > SAA7115_SVIDEO3)
		return -EINVAL;
	if (state->input == input && state->output == output)
		return 0;
	v4l2_dbg(1, debug, sd, "now setting %s input %s output\n",
		(input >= SAA7115_SVIDEO0) ? "S-Video" : "Composite",
		(output == SAA7115_IPORT_ON) ? "iport on" : "iport off");
	state->input = input;

	/* saa7111 has slightly different input numbering */
	if (state->ident <= V4L2_IDENT_SAA7111A) {
		if (input >= SAA7115_COMPOSITE4)
			input -= 2;
		/* saa7111 specific */
		saa711x_write(sd, R_10_CHROMA_CNTL_2,
				(saa711x_read(sd, R_10_CHROMA_CNTL_2) & 0x3f) |
				((output & 0xc0) ^ 0x40));
		saa711x_write(sd, R_13_RT_X_PORT_OUT_CNTL,
				(saa711x_read(sd, R_13_RT_X_PORT_OUT_CNTL) & 0xf0) |
				((output & 2) ? 0x0a : 0));
	}

	/* select mode */
	saa711x_write(sd, R_02_INPUT_CNTL_1,
		      (saa711x_read(sd, R_02_INPUT_CNTL_1) & mask) |
		       input);

	/* bypass chrominance trap for S-Video modes */
	saa711x_write(sd, R_09_LUMA_CNTL,
			(saa711x_read(sd, R_09_LUMA_CNTL) & 0x7f) |
			(state->input >= SAA7115_SVIDEO0 ? 0x80 : 0x0));

	state->output = output;
	if (state->ident == V4L2_IDENT_SAA7114 ||
			state->ident == V4L2_IDENT_SAA7115) {
		saa711x_write(sd, R_83_X_PORT_I_O_ENA_AND_OUT_CLK,
				(saa711x_read(sd, R_83_X_PORT_I_O_ENA_AND_OUT_CLK) & 0xfe) |
				(state->output & 0x01));
	}
	return 0;
}