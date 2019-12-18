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
struct usb_device {int dummy; } ;
struct gspca_dev {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int const) ; 
 int reg_write (struct usb_device*,int const,int const) ; 
 int ssi_w (struct gspca_dev*,int const,int const) ; 

__attribute__((used)) static int write_vector(struct gspca_dev *gspca_dev,
			const u16 (*data)[2])
{
	struct usb_device *dev = gspca_dev->dev;
	int ret = 0;

	while ((*data)[1] != 0) {
		if ((*data)[1] & 0x8000) {
			if ((*data)[1] == 0xdd00)	/* delay */
				msleep((*data)[0]);
			else
				ret = reg_write(dev, (*data)[1], (*data)[0]);
		} else {
			ret = ssi_w(gspca_dev, (*data)[1], (*data)[0]);
		}
		if (ret < 0)
			break;
		data++;
	}
	return ret;
}