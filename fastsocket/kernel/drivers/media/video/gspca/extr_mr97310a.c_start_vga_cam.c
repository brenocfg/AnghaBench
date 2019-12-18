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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct sensor_w_data {int member_0; int member_1; int member_3; TYPE_1__ member_2; } ;
struct sd {int sensor_type; scalar_t__ adj_colors; int /*<<< orphan*/  do_lcd_stop; } ;
struct gspca_dev {int* usb_buf; int width; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct sensor_w_data const*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int mr_write (struct gspca_dev*,int) ; 
 int sensor_write_regs (struct gspca_dev*,struct sensor_w_data const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_vga_cam(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 *data = gspca_dev->usb_buf;
	int err_code;
	static const __u8 startup_string[] =
		{0x00, 0x0d, 0x01, 0x00, 0x00, 0x2b, 0x00, 0x00,
		 0x00, 0x50, 0xc0};
	/* What some of these mean is explained in start_cif_cam(), above */

	memcpy(data, startup_string, 11);
	if (!sd->sensor_type) {
		data[5]  = 0x00;
		data[10] = 0x91;
	}
	if (sd->sensor_type == 2) {
		data[5]  = 0x00;
		data[10] = 0x18;
	}

	switch (gspca_dev->width) {
	case 160:
		data[9] |= 0x0c;  /* reg 8, 4:1 scale down */
		/* fall thru */
	case 320:
		data[9] |= 0x04;  /* reg 8, 2:1 scale down */
		/* fall thru */
	case 640:
	default:
		data[3] = 0x50;  /* reg 2, H size/8 */
		data[4] = 0x78;  /* reg 3, V size/4 */
		data[6] = 0x04;  /* reg 5, H start */
		data[8] = 0x03;  /* reg 7, V start */
		if (sd->sensor_type == 2) {
			data[6] = 2;
			data[8] = 1;
		}
		if (sd->do_lcd_stop)
			data[8] = 0x04;  /* Bayer tile shifted */
		break;

	case 176:
		data[9] |= 0x04;  /* reg 8, 2:1 scale down */
		/* fall thru */
	case 352:
		data[3] = 0x2c;  /* reg 2, H size */
		data[4] = 0x48;  /* reg 3, V size */
		data[6] = 0x94;  /* reg 5, H start */
		data[8] = 0x63;  /* reg 7, V start */
		if (sd->do_lcd_stop)
			data[8] = 0x64;  /* Bayer tile shifted */
		break;
	}

	err_code = mr_write(gspca_dev, 11);
	if (err_code < 0)
		return err_code;

	if (!sd->sensor_type) {
		static const struct sensor_w_data vga_sensor0_init_data[] = {
			{0x01, 0x00, {0x0c, 0x00, 0x04}, 3},
			{0x14, 0x00, {0x01, 0xe4, 0x02, 0x84}, 4},
			{0x20, 0x00, {0x00, 0x80, 0x00, 0x08}, 4},
			{0x25, 0x00, {0x03, 0xa9, 0x80}, 3},
			{0x30, 0x00, {0x30, 0x18, 0x10, 0x18}, 4},
			{0, 0, {0}, 0}
		};
		err_code = sensor_write_regs(gspca_dev, vga_sensor0_init_data,
					 ARRAY_SIZE(vga_sensor0_init_data));
	} else if (sd->sensor_type == 1) {
		static const struct sensor_w_data color_adj[] = {
			{0x02, 0x00, {0x06, 0x59, 0x0c, 0x16, 0x00,
				/* adjusted blue, green, red gain correct
				   too much blue from the Sakar Digital */
				0x05, 0x01, 0x04}, 8}
		};

		static const struct sensor_w_data color_no_adj[] = {
			{0x02, 0x00, {0x06, 0x59, 0x0c, 0x16, 0x00,
				/* default blue, green, red gain settings */
				0x07, 0x00, 0x01}, 8}
		};

		static const struct sensor_w_data vga_sensor1_init_data[] = {
			{0x11, 0x04, {0x01}, 1},
			{0x0a, 0x00, {0x00, 0x01, 0x00, 0x00, 0x01,
			/* These settings may be better for some cameras */
			/* {0x0a, 0x00, {0x01, 0x06, 0x00, 0x00, 0x01, */
				0x00, 0x0a}, 7},
			{0x11, 0x04, {0x01}, 1},
			{0x12, 0x00, {0x00, 0x63, 0x00, 0x70, 0x00, 0x00}, 6},
			{0x11, 0x04, {0x01}, 1},
			{0, 0, {0}, 0}
		};

		if (sd->adj_colors)
			err_code = sensor_write_regs(gspca_dev, color_adj,
					 ARRAY_SIZE(color_adj));
		else
			err_code = sensor_write_regs(gspca_dev, color_no_adj,
					 ARRAY_SIZE(color_no_adj));

		if (err_code < 0)
			return err_code;

		err_code = sensor_write_regs(gspca_dev, vga_sensor1_init_data,
					 ARRAY_SIZE(vga_sensor1_init_data));
	} else {	/* sensor type == 2 */
		static const struct sensor_w_data vga_sensor2_init_data[] = {

			{0x01, 0x00, {0x48}, 1},
			{0x02, 0x00, {0x22}, 1},
			/* Reg 3 msb and 4 is lsb of the exposure setting*/
			{0x05, 0x00, {0x10}, 1},
			{0x06, 0x00, {0x00}, 1},
			{0x07, 0x00, {0x00}, 1},
			{0x08, 0x00, {0x00}, 1},
			{0x09, 0x00, {0x00}, 1},
			/* The following are used in the gain control
			 * which is BTW completely borked in the OEM driver
			 * The values for each color go from 0 to 0x7ff
			 *{0x0a, 0x00, {0x01}, 1},  green1 gain msb
			 *{0x0b, 0x00, {0x10}, 1},  green1 gain lsb
			 *{0x0c, 0x00, {0x01}, 1},  red gain msb
			 *{0x0d, 0x00, {0x10}, 1},  red gain lsb
			 *{0x0e, 0x00, {0x01}, 1},  blue gain msb
			 *{0x0f, 0x00, {0x10}, 1},  blue gain lsb
			 *{0x10, 0x00, {0x01}, 1}, green2 gain msb
			 *{0x11, 0x00, {0x10}, 1}, green2 gain lsb
			 */
			{0x12, 0x00, {0x00}, 1},
			{0x13, 0x00, {0x04}, 1}, /* weird effect on colors */
			{0x14, 0x00, {0x00}, 1},
			{0x15, 0x00, {0x06}, 1},
			{0x16, 0x00, {0x01}, 1},
			{0x17, 0x00, {0xe2}, 1}, /* vertical alignment */
			{0x18, 0x00, {0x02}, 1},
			{0x19, 0x00, {0x82}, 1}, /* don't mess with */
			{0x1a, 0x00, {0x00}, 1},
			{0x1b, 0x00, {0x20}, 1},
			/* {0x1c, 0x00, {0x17}, 1}, contrast control */
			{0x1d, 0x00, {0x80}, 1}, /* moving causes a mess */
			{0x1e, 0x00, {0x08}, 1}, /* moving jams the camera */
			{0x1f, 0x00, {0x0c}, 1},
			{0x20, 0x00, {0x00}, 1},
			{0, 0, {0}, 0}
		};
		err_code = sensor_write_regs(gspca_dev, vga_sensor2_init_data,
					 ARRAY_SIZE(vga_sensor2_init_data));
	}
	return err_code;
}