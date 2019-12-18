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
struct usb_ov511 {unsigned char* cbuf; scalar_t__ bclass; int /*<<< orphan*/  cbuf_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,unsigned char) ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbolic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urb_errlist ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reg_w(struct usb_ov511 *ov, unsigned char reg, unsigned char value)
{
	int rc;

	PDEBUG(5, "0x%02X:0x%02X", reg, value);

	mutex_lock(&ov->cbuf_lock);
	ov->cbuf[0] = value;
	rc = usb_control_msg(ov->dev,
			     usb_sndctrlpipe(ov->dev, 0),
			     (ov->bclass == BCL_OV518)?1:2 /* REG_IO */,
			     USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			     0, (__u16)reg, &ov->cbuf[0], 1, 1000);
	mutex_unlock(&ov->cbuf_lock);

	if (rc < 0)
		err("reg write: error %d: %s", rc, symbolic(urb_errlist, rc));

	return rc;
}