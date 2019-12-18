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
typedef  int u8 ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct cs53l32a_state {int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int cs53l32a_read (struct v4l2_subdev*,int) ; 
 struct cs53l32a_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int cs53l32a_log_status(struct v4l2_subdev *sd)
{
	struct cs53l32a_state *state = to_state(sd);
	u8 v = cs53l32a_read(sd, 0x01);

	v4l2_info(sd, "Input:  %d\n", (v >> 4) & 3);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	return 0;
}