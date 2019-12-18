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
typedef  int /*<<< orphan*/  u8 ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int i2c_w(struct gspca_dev *gspca_dev, const u8 *buffer)
{
	int i;
	reg_w(gspca_dev, 0x10c0, buffer, 8);
	for (i = 0; i < 5; i++) {
		reg_r(gspca_dev, 0x10c0, 1);
		if (gspca_dev->usb_buf[0] & 0x04) {
			if (gspca_dev->usb_buf[0] & 0x08)
				return -EIO;
			return 0;
		}
		msleep(1);
	}
	return -EIO;
}