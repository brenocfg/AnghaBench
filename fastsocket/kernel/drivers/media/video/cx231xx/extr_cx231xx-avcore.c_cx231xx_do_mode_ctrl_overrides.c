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
struct cx231xx {int norm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFE_CTRL3 ; 
 int /*<<< orphan*/  FLD_HBLANK_CNT ; 
 int /*<<< orphan*/  FLD_V656BLANK_CNT ; 
 int /*<<< orphan*/  FLD_VACTIVE_CNT ; 
 int /*<<< orphan*/  FLD_VBLANK_CNT ; 
 int /*<<< orphan*/  HORIZ_TIM_CTRL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  VERT_TIM_CTRL ; 
 int /*<<< orphan*/  VID_BLK_I2C_ADDRESS ; 
 int /*<<< orphan*/  cx231xx_info (char*,...) ; 
 int cx231xx_read_modify_write_i2c_dword (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cx231xx_set_field (int /*<<< orphan*/ ,int) ; 
 int vid_blk_write_word (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

int cx231xx_do_mode_ctrl_overrides(struct cx231xx *dev)
{
	int status = 0;

	cx231xx_info("do_mode_ctrl_overrides : 0x%x\n",
		     (unsigned int)dev->norm);

	/* Change the DFE_CTRL3 bp_percent to fix flagging */
	status = vid_blk_write_word(dev, DFE_CTRL3, 0xCD3F0280);

	if (dev->norm & (V4L2_STD_NTSC | V4L2_STD_PAL_M)) {
		cx231xx_info("do_mode_ctrl_overrides NTSC\n");

		/* Move the close caption lines out of active video,
		   adjust the active video start point */
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VBLANK_CNT, 0x18);
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VACTIVE_CNT,
							0x1E7000);
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_V656BLANK_CNT,
							0x1C000000);

		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							HORIZ_TIM_CTRL,
							FLD_HBLANK_CNT,
							cx231xx_set_field
							(FLD_HBLANK_CNT, 0x79));

	} else if (dev->norm & V4L2_STD_SECAM) {
		cx231xx_info("do_mode_ctrl_overrides SECAM\n");
		status =  cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VBLANK_CNT, 0x20);
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VACTIVE_CNT,
							cx231xx_set_field
							(FLD_VACTIVE_CNT,
							 0x244));
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_V656BLANK_CNT,
							cx231xx_set_field
							(FLD_V656BLANK_CNT,
							0x24));
		/* Adjust the active video horizontal start point */
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							HORIZ_TIM_CTRL,
							FLD_HBLANK_CNT,
							cx231xx_set_field
							(FLD_HBLANK_CNT, 0x85));
	} else {
		cx231xx_info("do_mode_ctrl_overrides PAL\n");
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VBLANK_CNT, 0x20);
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VACTIVE_CNT,
							cx231xx_set_field
							(FLD_VACTIVE_CNT,
							 0x244));
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_V656BLANK_CNT,
							cx231xx_set_field
							(FLD_V656BLANK_CNT,
							0x24));
		/* Adjust the active video horizontal start point */
		status = cx231xx_read_modify_write_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							HORIZ_TIM_CTRL,
							FLD_HBLANK_CNT,
							cx231xx_set_field
							(FLD_HBLANK_CNT, 0x85));

	}

	return status;
}