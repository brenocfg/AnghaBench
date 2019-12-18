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
struct usb_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_2__ cam; struct usb_device* dev; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w_val (struct usb_device*,int,int) ; 
 int /*<<< orphan*/  rev72a_init_data1 ; 
 int /*<<< orphan*/  rev72a_init_sensor1 ; 
 int /*<<< orphan*/  rev72a_init_sensor2 ; 
 int /*<<< orphan*/  rev72a_reset ; 
 int /*<<< orphan*/  setautogain (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcontrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  write_sensor_72a (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start_72a(struct gspca_dev *gspca_dev)
{
	struct usb_device *dev = gspca_dev->dev;
	int Clck;
	int mode;

	write_vector(gspca_dev, rev72a_reset);
	msleep(200);
	write_vector(gspca_dev, rev72a_init_data1);
	write_sensor_72a(gspca_dev, rev72a_init_sensor1);

	mode = gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv;
	switch (mode) {
	default:
	case 0:
		Clck = 0x27;		/* ms-win 0x87 */
		break;
	case 1:
		Clck = 0x25;
		break;
	case 2:
		Clck = 0x22;
		break;
	case 3:
		Clck = 0x21;
		break;
	}
	reg_w_val(dev, 0x8700, Clck);	/* 0x27 clock */
	reg_w_val(dev, 0x8702, 0x81);
	reg_w_val(dev, 0x8500, mode);	/* mode */
	write_sensor_72a(gspca_dev, rev72a_init_sensor2);
	setcontrast(gspca_dev);
/*	setbrightness(gspca_dev);	 * fixme: bad values */
	setautogain(gspca_dev);
	reg_w_val(dev, 0x8112, 0x10 | 0x20);
	return 0;
}