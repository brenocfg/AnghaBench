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
struct usbduxfastsub_s {int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EZTIMEOUT ; 
 int /*<<< orphan*/  USBDUXFASTSUB_CPUCS ; 
 int /*<<< orphan*/  USBDUXFASTSUB_FIRMWARE ; 
 int /*<<< orphan*/  VENDOR_DIR_OUT ; 
 int /*<<< orphan*/  printk (char*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxfastsub_start(struct usbduxfastsub_s *udfs)
{
	int ret;
	unsigned char local_transfer_buffer[16];

	/* 7f92 to zero */
	local_transfer_buffer[0] = 0;
	ret = usb_control_msg(udfs->usbdev, usb_sndctrlpipe(udfs->usbdev, 0), USBDUXFASTSUB_FIRMWARE,	/* bRequest, "Firmware" */
			      VENDOR_DIR_OUT,	/* bmRequestType */
			      USBDUXFASTSUB_CPUCS,	/* Value */
			      0x0000,	/* Index */
			      local_transfer_buffer,	/* address of the transfer buffer */
			      1,	/* Length */
			      EZTIMEOUT);	/* Timeout */
	if (ret < 0) {
		printk("comedi_: usbduxfast_: control msg failed (start)\n");
		return ret;
	}

	return 0;
}