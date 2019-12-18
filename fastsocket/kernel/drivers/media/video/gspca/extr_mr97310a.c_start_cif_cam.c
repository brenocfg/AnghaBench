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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; } ;
struct sensor_w_data {int member_0; int member_1; int member_3; TYPE_1__ member_2; } ;
struct sd {int sensor_type; } ;
struct gspca_dev {int* usb_buf; int width; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct sensor_w_data const*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int mr_write (struct gspca_dev*,int) ; 
 int sensor_write_regs (struct gspca_dev*,struct sensor_w_data const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_cif_cam(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 *data = gspca_dev->usb_buf;
	int err_code;
	static const __u8 startup_string[] = {
		0x00,
		0x0d,
		0x01,
		0x00, /* Hsize/8 for 352 or 320 */
		0x00, /* Vsize/4 for 288 or 240 */
		0x13, /* or 0xbb, depends on sensor */
		0x00, /* Hstart, depends on res. */
		0x00, /* reserved ? */
		0x00, /* Vstart, depends on res. and sensor */
		0x50, /* 0x54 to get 176 or 160 */
		0xc0
	};

	/* Note: Some of the above descriptions guessed from MR97113A driver */

	memcpy(data, startup_string, 11);
	if (sd->sensor_type)
		data[5] = 0xbb;

	switch (gspca_dev->width) {
	case 160:
		data[9] |= 0x04;  /* reg 8, 2:1 scale down from 320 */
		/* fall thru */
	case 320:
	default:
		data[3] = 0x28;			   /* reg 2, H size/8 */
		data[4] = 0x3c;			   /* reg 3, V size/4 */
		data[6] = 0x14;			   /* reg 5, H start  */
		data[8] = 0x1a + sd->sensor_type;  /* reg 7, V start  */
		break;
	case 176:
		data[9] |= 0x04;  /* reg 8, 2:1 scale down from 352 */
		/* fall thru */
	case 352:
		data[3] = 0x2c;			   /* reg 2, H size/8 */
		data[4] = 0x48;			   /* reg 3, V size/4 */
		data[6] = 0x06;			   /* reg 5, H start  */
		data[8] = 0x06 - sd->sensor_type;  /* reg 7, V start  */
		break;
	}
	err_code = mr_write(gspca_dev, 11);
	if (err_code < 0)
		return err_code;

	if (!sd->sensor_type) {
		static const struct sensor_w_data cif_sensor0_init_data[] = {
			{0x02, 0x00, {0x03, 0x5a, 0xb5, 0x01,
				      0x0f, 0x14, 0x0f, 0x10}, 8},
			{0x0c, 0x00, {0x04, 0x01, 0x01, 0x00, 0x1f}, 5},
			{0x12, 0x00, {0x07}, 1},
			{0x1f, 0x00, {0x06}, 1},
			{0x27, 0x00, {0x04}, 1},
			{0x29, 0x00, {0x0c}, 1},
			{0x40, 0x00, {0x40, 0x00, 0x04}, 3},
			{0x50, 0x00, {0x60}, 1},
			{0x60, 0x00, {0x06}, 1},
			{0x6b, 0x00, {0x85, 0x85, 0xc8, 0xc8, 0xc8, 0xc8}, 6},
			{0x72, 0x00, {0x1e, 0x56}, 2},
			{0x75, 0x00, {0x58, 0x40, 0xa2, 0x02, 0x31, 0x02,
				      0x31, 0x80, 0x00}, 9},
			{0x11, 0x00, {0x01}, 1},
			{0, 0, {0}, 0}
		};
		err_code = sensor_write_regs(gspca_dev, cif_sensor0_init_data,
					 ARRAY_SIZE(cif_sensor0_init_data));
	} else {	/* sd->sensor_type = 1 */
		static const struct sensor_w_data cif_sensor1_init_data[] = {
			/* Reg 3,4, 7,8 get set by the controls */
			{0x02, 0x00, {0x10}, 1},
			{0x05, 0x01, {0x22}, 1}, /* 5/6 also seen as 65h/32h */
			{0x06, 0x01, {0x00}, 1},
			{0x09, 0x02, {0x0e}, 1},
			{0x0a, 0x02, {0x05}, 1},
			{0x0b, 0x02, {0x05}, 1},
			{0x0c, 0x02, {0x0f}, 1},
			{0x0d, 0x02, {0x07}, 1},
			{0x0e, 0x02, {0x0c}, 1},
			{0x0f, 0x00, {0x00}, 1},
			{0x10, 0x00, {0x06}, 1},
			{0x11, 0x00, {0x07}, 1},
			{0x12, 0x00, {0x00}, 1},
			{0x13, 0x00, {0x01}, 1},
			{0, 0, {0}, 0}
		};
		/* Without this command the cam won't work with USB-UHCI */
		gspca_dev->usb_buf[0] = 0x0a;
		gspca_dev->usb_buf[1] = 0x00;
		err_code = mr_write(gspca_dev, 2);
		if (err_code < 0)
			return err_code;
		err_code = sensor_write_regs(gspca_dev, cif_sensor1_init_data,
					 ARRAY_SIZE(cif_sensor1_init_data));
	}
	return err_code;
}