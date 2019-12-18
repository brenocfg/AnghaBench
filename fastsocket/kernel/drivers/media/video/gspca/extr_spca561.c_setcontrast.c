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
struct usb_device {int dummy; } ;
struct sd {scalar_t__ chip_revision; scalar_t__ contrast; } ;
struct gspca_dev {struct usb_device* dev; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 scalar_t__ Rev072A ; 
 int /*<<< orphan*/  reg_w_val (struct usb_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  setwhite (struct gspca_dev*) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct usb_device *dev = gspca_dev->dev;
	__u8 value;

	if (sd->chip_revision != Rev072A)
		return;
	value = sd->contrast + 0x20;

	/* gains for white balance */
	setwhite(gspca_dev);
/*	reg_w_val(dev, 0x8651, value);		 * R - done by setwhite */
	reg_w_val(dev, 0x8652, value);		/* Gr */
/*	reg_w_val(dev, 0x8653, value);		 * B - done by setwhite */
	reg_w_val(dev, 0x8654, value);		/* Gb */
}