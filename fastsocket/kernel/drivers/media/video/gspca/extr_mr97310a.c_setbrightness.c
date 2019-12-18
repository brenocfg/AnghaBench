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
struct sd {scalar_t__ cam_type; scalar_t__ brightness; scalar_t__ do_lcd_stop; } ;
struct gspca_dev {int ctrl_dis; } ;

/* Variables and functions */
 int ARGUS_QC_BRIGHTNESS_IDX ; 
 scalar_t__ CAM_TYPE_VGA ; 
 int NORM_BRIGHTNESS_IDX ; 
 int /*<<< orphan*/  sensor_write1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 val;
	u8 sign_reg = 7;  /* This reg and the next one used on CIF cams. */
	u8 value_reg = 8; /* VGA cams seem to use regs 0x0b and 0x0c */
	static const u8 quick_clix_table[] =
	/*	  0  1  2   3  4  5  6  7  8  9  10  11  12  13  14  15 */
		{ 0, 4, 8, 12, 1, 2, 3, 5, 6, 9,  7, 10, 13, 11, 14, 15};
	/*
	 * This control is disabled for CIF type 1 and VGA type 0 cameras.
	 * It does not quite act linearly for the Argus QuickClix camera,
	 * but it does control brightness. The values are 0 - 15 only, and
	 * the table above makes them act consecutively.
	 */
	if ((gspca_dev->ctrl_dis & (1 << NORM_BRIGHTNESS_IDX)) &&
	    (gspca_dev->ctrl_dis & (1 << ARGUS_QC_BRIGHTNESS_IDX)))
		return;

	if (sd->cam_type == CAM_TYPE_VGA) {
		sign_reg += 4;
		value_reg += 4;
	}

	/* Note register 7 is also seen as 0x8x or 0xCx in some dumps */
	if (sd->brightness > 0) {
		sensor_write1(gspca_dev, sign_reg, 0x00);
		val = sd->brightness;
	} else {
		sensor_write1(gspca_dev, sign_reg, 0x01);
		val = (257 - sd->brightness);
	}
	/* Use lookup table for funky Argus QuickClix brightness */
	if (sd->do_lcd_stop)
		val = quick_clix_table[val];

	sensor_write1(gspca_dev, value_reg, val);
}