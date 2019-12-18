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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {scalar_t__ init_curr_lens_pos; scalar_t__ curr_lens_pos; } ;

/* Variables and functions */
 int MT9T013_AF_I2C_ADDR ; 
 TYPE_1__* mt9t013_ctrl ; 
 int /*<<< orphan*/  mt9t013_i2c_write_b (int,int,int) ; 

__attribute__((used)) static int32_t mt9t013_set_default_focus(uint8_t af_step)
{
	int32_t rc = 0;
	uint8_t code_val_msb, code_val_lsb;
	code_val_msb = 0x01;
	code_val_lsb = af_step;

	/* Write the digital code for current to the actuator */
	rc = mt9t013_i2c_write_b(MT9T013_AF_I2C_ADDR>>1,
			code_val_msb, code_val_lsb);

	mt9t013_ctrl->curr_lens_pos = 0;
	mt9t013_ctrl->init_curr_lens_pos = 0;
	return rc;
}