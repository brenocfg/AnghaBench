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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct gspca_dev {void* usb_buf; struct usb_device* dev; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  err (char*,int,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int gl860_RTx(struct gspca_dev *gspca_dev,
		unsigned char pref, u32 req, u16 val, u16 index,
		s32 len, void *pdata)
{
	struct usb_device *udev = gspca_dev->dev;
	s32 r = 0;

	if (pref == 0x40) { /* Send */
		if (len > 0) {
			memcpy(gspca_dev->usb_buf, pdata, len);
			r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
					req, pref, val, index,
					gspca_dev->usb_buf,
					len, 400 + 200 * (len > 1));
		} else {
			r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
					req, pref, val, index, NULL, len, 400);
		}
	} else { /* Receive */
		if (len > 0) {
			r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
					req, pref, val, index,
					gspca_dev->usb_buf,
					len, 400 + 200 * (len > 1));
			memcpy(pdata, gspca_dev->usb_buf, len);
		} else {
			r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
					req, pref, val, index, NULL, len, 400);
		}
	}

	if (r < 0)
		err("ctrl transfer failed %4d "
			"[p%02x r%d v%04x i%04x len%d]",
			r, pref, req, val, index, len);
	else if (len > 1 && r < len)
		PDEBUG(D_ERR, "short ctrl transfer %d/%d", r, len);

	msleep(1);

	return r;
}