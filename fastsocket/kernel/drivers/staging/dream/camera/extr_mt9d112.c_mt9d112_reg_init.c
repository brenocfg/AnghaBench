#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {size_t prev_snap_reg_settings_size; size_t noise_reduction_reg_settings_size; int /*<<< orphan*/  stbl_size; int /*<<< orphan*/ * stbl; TYPE_2__* noise_reduction_reg_settings; TYPE_1__* prev_snap_reg_settings; int /*<<< orphan*/  plltbl_size; int /*<<< orphan*/ * plltbl; } ;
struct TYPE_6__ {int register_address; int register_value; } ;
struct TYPE_5__ {int register_address; int register_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORD_LEN ; 
 TYPE_4__* mt9d112_client ; 
 long mt9d112_i2c_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 long mt9d112_i2c_write_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ mt9d112_regs ; 
 long mt9d112_set_lens_roll_off () ; 

__attribute__((used)) static long mt9d112_reg_init(void)
{
	int32_t array_length;
	int32_t i;
	long rc;

	/* PLL Setup Start */
	rc = mt9d112_i2c_write_table(&mt9d112_regs.plltbl[0],
					mt9d112_regs.plltbl_size);

	if (rc < 0)
		return rc;
	/* PLL Setup End   */

	array_length = mt9d112_regs.prev_snap_reg_settings_size;

	/* Configure sensor for Preview mode and Snapshot mode */
	for (i = 0; i < array_length; i++) {
		rc = mt9d112_i2c_write(mt9d112_client->addr,
		  mt9d112_regs.prev_snap_reg_settings[i].register_address,
		  mt9d112_regs.prev_snap_reg_settings[i].register_value,
		  WORD_LEN);

		if (rc < 0)
			return rc;
	}

	/* Configure for Noise Reduction, Saturation and Aperture Correction */
	array_length = mt9d112_regs.noise_reduction_reg_settings_size;

	for (i = 0; i < array_length; i++) {
		rc = mt9d112_i2c_write(mt9d112_client->addr,
			mt9d112_regs.noise_reduction_reg_settings[i].register_address,
			mt9d112_regs.noise_reduction_reg_settings[i].register_value,
			WORD_LEN);

		if (rc < 0)
			return rc;
	}

	/* Set Color Kill Saturation point to optimum value */
	rc =
	mt9d112_i2c_write(mt9d112_client->addr,
	0x35A4,
	0x0593,
	WORD_LEN);
	if (rc < 0)
		return rc;

	rc = mt9d112_i2c_write_table(&mt9d112_regs.stbl[0],
					mt9d112_regs.stbl_size);
	if (rc < 0)
		return rc;

	rc = mt9d112_set_lens_roll_off();
	if (rc < 0)
		return rc;

	return 0;
}