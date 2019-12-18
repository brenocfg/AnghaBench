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
typedef  int u16 ;
struct gspca_dev {int usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int OV534_REG_ADDRESS ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bridge_init ; 
 int /*<<< orphan*/  bridge_init_2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sccb_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  sensor_init ; 
 int /*<<< orphan*/  sensor_init_2 ; 
 int /*<<< orphan*/  set_led (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	u16 sensor_id;

	/* reset bridge */
	reg_w(gspca_dev, 0xe7, 0x3a);
	reg_w(gspca_dev, 0xe0, 0x08);
	msleep(100);

	/* initialize the sensor address */
	reg_w(gspca_dev, OV534_REG_ADDRESS, 0x60);

	/* reset sensor */
	sccb_write(gspca_dev, 0x12, 0x80);
	msleep(10);

	/* probe the sensor */
	sccb_read(gspca_dev, 0x0a);
	sensor_id = sccb_read(gspca_dev, 0x0a) << 8;
	sccb_read(gspca_dev, 0x0b);
	sensor_id |= sccb_read(gspca_dev, 0x0b);
	PDEBUG(D_PROBE, "Sensor ID: %04x", sensor_id);

	/* initialize */
	reg_w_array(gspca_dev, bridge_init,
			ARRAY_SIZE(bridge_init));
	sccb_w_array(gspca_dev, sensor_init,
			ARRAY_SIZE(sensor_init));
	reg_w_array(gspca_dev, bridge_init_2,
			ARRAY_SIZE(bridge_init_2));
	sccb_w_array(gspca_dev, sensor_init_2,
			ARRAY_SIZE(sensor_init_2));
	reg_w(gspca_dev, 0xe0, 0x00);
	reg_w(gspca_dev, 0xe0, 0x01);
	set_led(gspca_dev, 0);
	reg_w(gspca_dev, 0xe0, 0x00);

	return gspca_dev->usb_err;
}