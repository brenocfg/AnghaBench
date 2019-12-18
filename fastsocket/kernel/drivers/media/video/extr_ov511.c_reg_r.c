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
struct usb_ov511 {scalar_t__ bclass; int* cbuf; int /*<<< orphan*/  cbuf_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,int) ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbolic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urb_errlist ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reg_r(struct usb_ov511 *ov, unsigned char reg)
{
	int rc;

	mutex_lock(&ov->cbuf_lock);
	rc = usb_control_msg(ov->dev,
			     usb_rcvctrlpipe(ov->dev, 0),
			     (ov->bclass == BCL_OV518)?1:3 /* REG_IO */,
			     USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			     0, (__u16)reg, &ov->cbuf[0], 1, 1000);

	if (rc < 0) {
		err("reg read: error %d: %s", rc, symbolic(urb_errlist, rc));
	} else {
		rc = ov->cbuf[0];
		PDEBUG(5, "0x%02X:0x%02X", reg, ov->cbuf[0]);
	}

	mutex_unlock(&ov->cbuf_lock);

	return rc;
}