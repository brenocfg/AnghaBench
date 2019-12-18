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
typedef  int u16 ;
struct gspca_dev {void** usb_buf; } ;

/* Variables and functions */
 int cpia_usb_transferCmd (struct gspca_dev*,void**) ; 

__attribute__((used)) static int do_command_extended(struct gspca_dev *gspca_dev, u16 command,
			       u8 a, u8 b, u8 c, u8 d,
			       u8 e, u8 f, u8 g, u8 h,
			       u8 i, u8 j, u8 k, u8 l)
{
	u8 cmd[8];

	cmd[0] = command >> 8;
	cmd[1] = command & 0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = 8;
	cmd[7] = 0;
	gspca_dev->usb_buf[0] = e;
	gspca_dev->usb_buf[1] = f;
	gspca_dev->usb_buf[2] = g;
	gspca_dev->usb_buf[3] = h;
	gspca_dev->usb_buf[4] = i;
	gspca_dev->usb_buf[5] = j;
	gspca_dev->usb_buf[6] = k;
	gspca_dev->usb_buf[7] = l;

	return cpia_usb_transferCmd(gspca_dev, cmd);
}