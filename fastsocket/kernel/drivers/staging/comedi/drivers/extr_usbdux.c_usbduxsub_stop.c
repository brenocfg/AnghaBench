#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usbduxsub {TYPE_1__* interface; int /*<<< orphan*/  usbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EZTIMEOUT ; 
 int /*<<< orphan*/  USBDUXSUB_CPUCS ; 
 int /*<<< orphan*/  USBDUXSUB_FIRMWARE ; 
 int /*<<< orphan*/  VENDOR_DIR_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsub_stop(struct usbduxsub *usbduxsub)
{
	int errcode = 0;

	uint8_t local_transfer_buffer[16];

	/* 7f92 to one */
	local_transfer_buffer[0] = 1;
	errcode = usb_control_msg(usbduxsub->usbdev,
				  usb_sndctrlpipe(usbduxsub->usbdev, 0),
				  /* bRequest, "Firmware" */
				  USBDUXSUB_FIRMWARE,
				  /* bmRequestType */
				  VENDOR_DIR_OUT,
				  /* Value */
				  USBDUXSUB_CPUCS,
				  /* Index */
				  0x0000, local_transfer_buffer,
				  /* Length */
				  1,
				  /* Timeout */
				  EZTIMEOUT);
	if (errcode < 0) {
		dev_err(&usbduxsub->interface->dev,
			"comedi_: control msg failed (stop)\n");
		return errcode;
	}
	return 0;
}