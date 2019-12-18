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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct flexcop_usb {int /*<<< orphan*/  udev; } ;
struct flexcop_device {struct flexcop_usb* bus_specific; } ;

/* Variables and functions */
 int B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2C2_USB_CTRL_PIPE_IN ; 
 int /*<<< orphan*/  B2C2_USB_CTRL_PIPE_OUT ; 
 int B2C2_USB_READ_REG ; 
 int B2C2_USB_WRITE_REG ; 
 int B2C2_WAIT_FOR_OPERATION_RDW ; 
 int EIO ; 
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,char*,int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int flexcop_usb_readwrite_dw(struct flexcop_device *fc, u16 wRegOffsPCI, u32 *val, u8 read)
{
	struct flexcop_usb *fc_usb = fc->bus_specific;
	u8 request = read ? B2C2_USB_READ_REG : B2C2_USB_WRITE_REG;
	u8 request_type = (read ? USB_DIR_IN : USB_DIR_OUT) | USB_TYPE_VENDOR;
	u8 wAddress = B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR(wRegOffsPCI) |
		(read ? 0x80 : 0);

	int len = usb_control_msg(fc_usb->udev,
			read ? B2C2_USB_CTRL_PIPE_IN : B2C2_USB_CTRL_PIPE_OUT,
			request,
			request_type, /* 0xc0 read or 0x40 write */
			wAddress,
			0,
			val,
			sizeof(u32),
			B2C2_WAIT_FOR_OPERATION_RDW * HZ);

	if (len != sizeof(u32)) {
		err("error while %s dword from %d (%d).", read ? "reading" :
				"writing", wAddress, wRegOffsPCI);
		return -EIO;
	}
	return 0;
}