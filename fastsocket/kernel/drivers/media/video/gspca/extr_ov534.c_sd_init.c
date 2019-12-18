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
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ov534_reg_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  ov534_set_led (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sccb_reg_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  sccb_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sensor_init ; 
 int /*<<< orphan*/  set_frame_rate (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	u16 sensor_id;

	/* reset bridge */
	ov534_reg_write(gspca_dev, 0xe7, 0x3a);
	ov534_reg_write(gspca_dev, 0xe0, 0x08);
	msleep(100);

	/* initialize the sensor address */
	ov534_reg_write(gspca_dev, OV534_REG_ADDRESS, 0x42);

	/* reset sensor */
	sccb_reg_write(gspca_dev, 0x12, 0x80);
	msleep(10);

	/* probe the sensor */
	sccb_reg_read(gspca_dev, 0x0a);
	sensor_id = sccb_reg_read(gspca_dev, 0x0a) << 8;
	sccb_reg_read(gspca_dev, 0x0b);
	sensor_id |= sccb_reg_read(gspca_dev, 0x0b);
	PDEBUG(D_PROBE, "Sensor ID: %04x", sensor_id);

	/* initialize */
	reg_w_array(gspca_dev, bridge_init,
			ARRAY_SIZE(bridge_init));
	ov534_set_led(gspca_dev, 1);
	sccb_w_array(gspca_dev, sensor_init,
			ARRAY_SIZE(sensor_init));
	ov534_reg_write(gspca_dev, 0xe0, 0x09);
	ov534_set_led(gspca_dev, 0);
	set_frame_rate(gspca_dev);

	return gspca_dev->usb_err;
}