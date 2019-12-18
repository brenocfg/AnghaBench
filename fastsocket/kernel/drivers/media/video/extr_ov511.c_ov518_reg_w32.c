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
struct usb_ov511 {int /*<<< orphan*/  cbuf_lock; scalar_t__ cbuf; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,int /*<<< orphan*/ ,int) ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbolic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urb_errlist ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ov518_reg_w32(struct usb_ov511 *ov, unsigned char reg, u32 val, int n)
{
	int rc;

	PDEBUG(5, "0x%02X:%7d, n=%d", reg, val, n);

	mutex_lock(&ov->cbuf_lock);

	*((__le32 *)ov->cbuf) = __cpu_to_le32(val);

	rc = usb_control_msg(ov->dev,
			     usb_sndctrlpipe(ov->dev, 0),
			     1 /* REG_IO */,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			     0, (__u16)reg, ov->cbuf, n, 1000);
	mutex_unlock(&ov->cbuf_lock);

	if (rc < 0)
		err("reg write multiple: error %d: %s", rc,
		    symbolic(urb_errlist, rc));

	return rc;
}