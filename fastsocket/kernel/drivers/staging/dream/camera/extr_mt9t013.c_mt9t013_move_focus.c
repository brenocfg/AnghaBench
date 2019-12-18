#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;
struct TYPE_2__ {int curr_lens_pos; int init_curr_lens_pos; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ EINVAL ; 
 int MOVE_FAR ; 
 int MOVE_NEAR ; 
 int MT9T013_AF_I2C_ADDR ; 
 scalar_t__ MT9T013_TOTAL_STEPS_NEAR_TO_FAR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* mt9t013_ctrl ; 
 scalar_t__ mt9t013_i2c_write_b (int,int,int) ; 

__attribute__((used)) static int32_t mt9t013_move_focus(int direction, int32_t num_steps)
{
	int16_t step_direction;
	int16_t actual_step;
	int16_t next_position;
	int16_t break_steps[4];
	uint8_t code_val_msb, code_val_lsb;
	int16_t i;

	if (num_steps > MT9T013_TOTAL_STEPS_NEAR_TO_FAR)
		num_steps = MT9T013_TOTAL_STEPS_NEAR_TO_FAR;
	else if (num_steps == 0)
		return -EINVAL;

	if (direction == MOVE_NEAR)
		step_direction = 4;
	else if (direction == MOVE_FAR)
		step_direction = -4;
	else
		return -EINVAL;

	if (mt9t013_ctrl->curr_lens_pos < mt9t013_ctrl->init_curr_lens_pos)
		mt9t013_ctrl->curr_lens_pos = mt9t013_ctrl->init_curr_lens_pos;

	actual_step =
		(int16_t) (step_direction *
		(int16_t) num_steps);

	for (i = 0; i < 4; i++)
		break_steps[i] =
			actual_step / 4 * (i + 1) - actual_step / 4 * i;

	for (i = 0; i < 4; i++) {
		next_position =
		(int16_t)
		(mt9t013_ctrl->curr_lens_pos + break_steps[i]);

		if (next_position > 255)
			next_position = 255;
		else if (next_position < 0)
			next_position = 0;

		code_val_msb =
		((next_position >> 4) << 2) |
		((next_position << 4) >> 6);

		code_val_lsb =
		((next_position & 0x03) << 6);

		/* Writing the digital code for current to the actuator */
		if (mt9t013_i2c_write_b(MT9T013_AF_I2C_ADDR>>1,
				code_val_msb, code_val_lsb) < 0)
			return -EBUSY;

		/* Storing the current lens Position */
		mt9t013_ctrl->curr_lens_pos = next_position;

		if (i < 3)
			mdelay(1);
	} /* for */

	return 0;
}