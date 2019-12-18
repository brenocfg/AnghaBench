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
struct gspca_dev {int* usb_buf; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int i2c_w(struct gspca_dev *gspca_dev, const __u8 *buffer)
{
	int retry = 60;

	/* is i2c ready */
	reg_w(gspca_dev, 0x08, buffer, 8);
	while (retry--) {
		msleep(10);
		reg_r(gspca_dev, 0x08);
		if (gspca_dev->usb_buf[0] & 0x04) {
			if (gspca_dev->usb_buf[0] & 0x08)
				return -1;
			return 0;
		}
	}
	return -1;
}