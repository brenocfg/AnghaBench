#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; int usb_err; TYPE_2__ cam; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_start_qvga ; 
 int /*<<< orphan*/  bridge_start_vga ; 
 int /*<<< orphan*/  ov534_reg_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  ov534_set_led (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_w_array (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sensor_start_qvga ; 
 int /*<<< orphan*/  sensor_start_vga ; 
 int /*<<< orphan*/  set_frame_rate (struct gspca_dev*) ; 
 int /*<<< orphan*/  setaec (struct gspca_dev*) ; 
 int /*<<< orphan*/  setagc (struct gspca_dev*) ; 
 int /*<<< orphan*/  setawb (struct gspca_dev*) ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcontrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  setfreqfltr (struct gspca_dev*) ; 
 int /*<<< orphan*/  setgain (struct gspca_dev*) ; 
 int /*<<< orphan*/  sethflip (struct gspca_dev*) ; 
 int /*<<< orphan*/  setsharpness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setvflip (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	int mode;

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	if (mode != 0) {	/* 320x240 */
		reg_w_array(gspca_dev, bridge_start_qvga,
				ARRAY_SIZE(bridge_start_qvga));
		sccb_w_array(gspca_dev, sensor_start_qvga,
				ARRAY_SIZE(sensor_start_qvga));
	} else {		/* 640x480 */
		reg_w_array(gspca_dev, bridge_start_vga,
				ARRAY_SIZE(bridge_start_vga));
		sccb_w_array(gspca_dev, sensor_start_vga,
				ARRAY_SIZE(sensor_start_vga));
	}
	set_frame_rate(gspca_dev);

	setagc(gspca_dev);
	setawb(gspca_dev);
	setaec(gspca_dev);
	setgain(gspca_dev);
	setexposure(gspca_dev);
	setbrightness(gspca_dev);
	setcontrast(gspca_dev);
	setsharpness(gspca_dev);
	setvflip(gspca_dev);
	sethflip(gspca_dev);
	setfreqfltr(gspca_dev);

	ov534_set_led(gspca_dev, 1);
	ov534_reg_write(gspca_dev, 0xe0, 0x00);
	return gspca_dev->usb_err;
}