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
typedef  void* u8 ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,void* const*,int) ; 
 int mr_write (struct gspca_dev*,int) ; 

__attribute__((used)) static int sensor_write_reg(struct gspca_dev *gspca_dev, u8 reg, u8 flags,
	const u8 *data, int len)
{
	gspca_dev->usb_buf[0] = 0x1f;
	gspca_dev->usb_buf[1] = flags;
	gspca_dev->usb_buf[2] = reg;
	memcpy(gspca_dev->usb_buf + 3, data, len);

	return mr_write(gspca_dev, len + 3);
}