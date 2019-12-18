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
struct au8522_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_CLAMPING_CONTROL_REG083H ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H ; 
 int AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13 ; 
 int /*<<< orphan*/  AU8522_MODULE_CLOCK_CONTROL_REG0A3H ; 
 int AU8522_MODULE_CLOCK_CONTROL_REG0A3H_SVIDEO ; 
 int /*<<< orphan*/  AU8522_PGA_CONTROL_REG082H ; 
 int /*<<< orphan*/  AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H ; 
 int AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_decoder_defaults (struct au8522_state*,int) ; 

__attribute__((used)) static void au8522_setup_svideo_mode(struct au8522_state *state)
{
	au8522_writereg(state, AU8522_MODULE_CLOCK_CONTROL_REG0A3H,
			AU8522_MODULE_CLOCK_CONTROL_REG0A3H_SVIDEO);

	/* Set input to Y on Channe1, C on Channel 3 */
	au8522_writereg(state, AU8522_INPUT_CONTROL_REG081H,
			AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13);

	/* PGA in automatic mode */
	au8522_writereg(state, AU8522_PGA_CONTROL_REG082H, 0x00);

	/* Enable clamping control */
	au8522_writereg(state, AU8522_CLAMPING_CONTROL_REG083H, 0x00);

	setup_decoder_defaults(state,
			       AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13);

	au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS);
}