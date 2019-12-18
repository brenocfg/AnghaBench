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
typedef  scalar_t__ u16 ;
struct gspca_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_BUF_SZ ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w_buf(struct gspca_dev *gspca_dev,
		  const u8 *buffer, u16 len)
{
	if (len <= USB_BUF_SZ) {
		memcpy(gspca_dev->usb_buf, buffer, len);
		usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,
			   USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x01, 0,
				gspca_dev->usb_buf, len, 500);
	} else {
		u8 *tmpbuf;

		tmpbuf = kmemdup(buffer, len, GFP_KERNEL);
		if (!tmpbuf) {
			err("Out of memory");
			return;
		}
		usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,
			   USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x01, 0,
				tmpbuf, len, 500);
		kfree(tmpbuf);
	}
}