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
typedef  int u16 ;
struct gspca_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USB_BUF_SZ ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w_ixbuf(struct gspca_dev *gspca_dev,
			u8 reg,
			const u8 *buffer, u16 len)
{
	int i;
	u8 *p, *tmpbuf;

	if (len * 2 <= USB_BUF_SZ) {
		p = tmpbuf = gspca_dev->usb_buf;
	} else {
		p = tmpbuf = kmalloc(len * 2, GFP_KERNEL);
		if (!tmpbuf) {
			err("Out of memory");
			return;
		}
	}
	i = len;
	while (--i >= 0) {
		*p++ = reg++;
		*p++ = *buffer++;
	}
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x01, 0,
			tmpbuf, len * 2, 500);
	if (len * 2 > USB_BUF_SZ)
		kfree(tmpbuf);
}