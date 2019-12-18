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
struct gspca_dev {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct usb_device*,int,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct usb_device *dev = gspca_dev->dev;

	reg_w(dev, 0x02, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0x00, 0x0003);
}