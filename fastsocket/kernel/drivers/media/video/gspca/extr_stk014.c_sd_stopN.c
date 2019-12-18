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
struct gspca_dev {int /*<<< orphan*/  iface; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rcv_val (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_par (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  snd_val (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct usb_device *dev = gspca_dev->dev;

	set_par(gspca_dev, 0x02000000);
	set_par(gspca_dev, 0x02000000);
	usb_set_interface(dev, gspca_dev->iface, 1);
	reg_r(gspca_dev, 0x0630);
	rcv_val(gspca_dev, 0x000020);	/* << (value ff ff ff ff) */
	reg_r(gspca_dev, 0x0650);
	snd_val(gspca_dev, 0x000020, 0xffffffff);
	reg_w(gspca_dev, 0x0620, 0);
	reg_w(gspca_dev, 0x0630, 0);
	reg_w(gspca_dev, 0x0640, 0);
	reg_w(gspca_dev, 0x0650, 0);
	reg_w(gspca_dev, 0x0660, 0);
	PDEBUG(D_STREAM, "camera stopped");
}