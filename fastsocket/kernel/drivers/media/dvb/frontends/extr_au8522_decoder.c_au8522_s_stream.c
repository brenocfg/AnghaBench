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
struct au8522_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H ; 
 int AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct au8522_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int au8522_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct au8522_state *state = to_state(sd);

	if (enable) {
		au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				0x01);
		msleep(1);
		au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS);
	} else {
		/* This does not completely power down the device
		   (it only reduces it from around 140ma to 80ma) */
		au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				1 << 5);
	}
	return 0;
}