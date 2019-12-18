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
typedef  int u32 ;
struct regs_cs4382 {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; int member_16; int /*<<< orphan*/  vol_control_B4; int /*<<< orphan*/  vol_control_A4; int /*<<< orphan*/  mix_control_P4; int /*<<< orphan*/  vol_control_B3; int /*<<< orphan*/  vol_control_A3; int /*<<< orphan*/  mix_control_P3; int /*<<< orphan*/  vol_control_B2; int /*<<< orphan*/  vol_control_A2; int /*<<< orphan*/  mix_control_P2; int /*<<< orphan*/  vol_control_B1; int /*<<< orphan*/  vol_control_A1; int /*<<< orphan*/  mix_control_P1; int /*<<< orphan*/  invert_control; int /*<<< orphan*/  filter_control; int /*<<< orphan*/  mode_control_3; int /*<<< orphan*/  mode_control_2; int /*<<< orphan*/  mode_control_1; } ;
struct hw {int dummy; } ;
struct dac_conf {int msr; } ;
typedef  int /*<<< orphan*/  cs_read ;

/* Variables and functions */
 int /*<<< orphan*/  CS4382_FC ; 
 int /*<<< orphan*/  CS4382_IC ; 
 int /*<<< orphan*/  CS4382_MC1 ; 
 int /*<<< orphan*/  CS4382_MC2 ; 
 int /*<<< orphan*/  CS4382_MC3 ; 
 int /*<<< orphan*/  CS4382_VCA1 ; 
 int /*<<< orphan*/  CS4382_VCA2 ; 
 int /*<<< orphan*/  CS4382_VCA3 ; 
 int /*<<< orphan*/  CS4382_VCA4 ; 
 int /*<<< orphan*/  CS4382_VCB1 ; 
 int /*<<< orphan*/  CS4382_VCB2 ; 
 int /*<<< orphan*/  CS4382_VCB3 ; 
 int /*<<< orphan*/  CS4382_VCB4 ; 
 int /*<<< orphan*/  CS4382_XC1 ; 
 int /*<<< orphan*/  CS4382_XC2 ; 
 int /*<<< orphan*/  CS4382_XC3 ; 
 int /*<<< orphan*/  CS4382_XC4 ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  GPIO_DATA ; 
 int hw20k2_i2c_init (struct hw*,int,int,int) ; 
 scalar_t__ hw20k2_i2c_read (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw20k2_i2c_uninit (struct hw*) ; 
 int /*<<< orphan*/  hw20k2_i2c_write (struct hw*,int /*<<< orphan*/ ,int) ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ memcmp (struct regs_cs4382*,struct regs_cs4382*,int) ; 

__attribute__((used)) static int hw_dac_init(struct hw *hw, const struct dac_conf *info)
{
	int err;
	u32 data;
	int i;
	struct regs_cs4382 cs_read = {0};
	struct regs_cs4382 cs_def = {
				   0x00000001,  /* Mode Control 1 */
				   0x00000000,  /* Mode Control 2 */
				   0x00000084,  /* Mode Control 3 */
				   0x00000000,  /* Filter Control */
				   0x00000000,  /* Invert Control */
				   0x00000024,  /* Mixing Control Pair 1 */
				   0x00000000,  /* Vol Control A1 */
				   0x00000000,  /* Vol Control B1 */
				   0x00000024,  /* Mixing Control Pair 2 */
				   0x00000000,  /* Vol Control A2 */
				   0x00000000,  /* Vol Control B2 */
				   0x00000024,  /* Mixing Control Pair 3 */
				   0x00000000,  /* Vol Control A3 */
				   0x00000000,  /* Vol Control B3 */
				   0x00000024,  /* Mixing Control Pair 4 */
				   0x00000000,  /* Vol Control A4 */
				   0x00000000   /* Vol Control B4 */
				 };

	/* Set DAC reset bit as output */
	data = hw_read_20kx(hw, GPIO_CTRL);
	data |= 0x02;
	hw_write_20kx(hw, GPIO_CTRL, data);

	err = hw20k2_i2c_init(hw, 0x18, 1, 1);
	if (err < 0)
		goto End;

	for (i = 0; i < 2; i++) {
		/* Reset DAC twice just in-case the chip
		 * didn't initialized properly */
		data = hw_read_20kx(hw, GPIO_DATA);
		/* GPIO data bit 1 */
		data &= 0xFFFFFFFD;
		hw_write_20kx(hw, GPIO_DATA, data);
		mdelay(10);
		data |= 0x2;
		hw_write_20kx(hw, GPIO_DATA, data);
		mdelay(50);

		/* Reset the 2nd time */
		data &= 0xFFFFFFFD;
		hw_write_20kx(hw, GPIO_DATA, data);
		mdelay(10);
		data |= 0x2;
		hw_write_20kx(hw, GPIO_DATA, data);
		mdelay(50);

		if (hw20k2_i2c_read(hw, CS4382_MC1,  &cs_read.mode_control_1))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_MC2,  &cs_read.mode_control_2))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_MC3,  &cs_read.mode_control_3))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_FC,   &cs_read.filter_control))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_IC,   &cs_read.invert_control))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_XC1,  &cs_read.mix_control_P1))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCA1, &cs_read.vol_control_A1))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCB1, &cs_read.vol_control_B1))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_XC2,  &cs_read.mix_control_P2))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCA2, &cs_read.vol_control_A2))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCB2, &cs_read.vol_control_B2))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_XC3,  &cs_read.mix_control_P3))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCA3, &cs_read.vol_control_A3))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCB3, &cs_read.vol_control_B3))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_XC4,  &cs_read.mix_control_P4))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCA4, &cs_read.vol_control_A4))
			continue;

		if (hw20k2_i2c_read(hw, CS4382_VCB4, &cs_read.vol_control_B4))
			continue;

		if (memcmp(&cs_read, &cs_def, sizeof(cs_read)))
			continue;
		else
			break;
	}

	if (i >= 2)
		goto End;

	/* Note: Every I2C write must have some delay.
	 * This is not a requirement but the delay works here... */
	hw20k2_i2c_write(hw, CS4382_MC1, 0x80);
	hw20k2_i2c_write(hw, CS4382_MC2, 0x10);
	if (1 == info->msr) {
		hw20k2_i2c_write(hw, CS4382_XC1, 0x24);
		hw20k2_i2c_write(hw, CS4382_XC2, 0x24);
		hw20k2_i2c_write(hw, CS4382_XC3, 0x24);
		hw20k2_i2c_write(hw, CS4382_XC4, 0x24);
	} else if (2 == info->msr) {
		hw20k2_i2c_write(hw, CS4382_XC1, 0x25);
		hw20k2_i2c_write(hw, CS4382_XC2, 0x25);
		hw20k2_i2c_write(hw, CS4382_XC3, 0x25);
		hw20k2_i2c_write(hw, CS4382_XC4, 0x25);
	} else {
		hw20k2_i2c_write(hw, CS4382_XC1, 0x26);
		hw20k2_i2c_write(hw, CS4382_XC2, 0x26);
		hw20k2_i2c_write(hw, CS4382_XC3, 0x26);
		hw20k2_i2c_write(hw, CS4382_XC4, 0x26);
	}

	return 0;
End:

	hw20k2_i2c_uninit(hw);
	return -1;
}