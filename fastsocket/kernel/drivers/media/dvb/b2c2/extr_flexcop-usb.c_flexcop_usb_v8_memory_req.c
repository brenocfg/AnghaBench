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
typedef  int u32 ;
typedef  int u16 ;
struct flexcop_usb {int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  flexcop_usb_request_t ;

/* Variables and functions */
 int B2C2_USB_CTRL_PIPE_IN ; 
 int B2C2_USB_CTRL_PIPE_OUT ; 
#define  B2C2_USB_FLASH_BLOCK 130 
#define  B2C2_USB_READ_V8_MEM 129 
#define  B2C2_USB_WRITE_V8_MEM 128 
 int B2C2_WAIT_FOR_OPERATION_V8FLASH ; 
 int B2C2_WAIT_FOR_OPERATION_V8READ ; 
 int B2C2_WAIT_FOR_OPERATION_V8WRITE ; 
 int EINVAL ; 
 int EIO ; 
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deb_v8 (char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*,int,int /*<<< orphan*/ ,int,int,int)) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int*,int,int) ; 

__attribute__((used)) static int flexcop_usb_v8_memory_req(struct flexcop_usb *fc_usb,
		flexcop_usb_request_t req, u8 page, u16 wAddress,
		u8 *pbBuffer, u32 buflen)
{
	u8 request_type = USB_TYPE_VENDOR;
	u16 wIndex;
	int nWaitTime, pipe, len;
	wIndex = page << 8;

	switch (req) {
	case B2C2_USB_READ_V8_MEM:
		nWaitTime = B2C2_WAIT_FOR_OPERATION_V8READ;
		request_type |= USB_DIR_IN;
		pipe = B2C2_USB_CTRL_PIPE_IN;
		break;
	case B2C2_USB_WRITE_V8_MEM:
		wIndex |= pbBuffer[0];
		request_type |= USB_DIR_OUT;
		nWaitTime = B2C2_WAIT_FOR_OPERATION_V8WRITE;
		pipe = B2C2_USB_CTRL_PIPE_OUT;
		break;
	case B2C2_USB_FLASH_BLOCK:
		request_type |= USB_DIR_OUT;
		nWaitTime = B2C2_WAIT_FOR_OPERATION_V8FLASH;
		pipe = B2C2_USB_CTRL_PIPE_OUT;
		break;
	default:
		deb_info("unsupported request for v8_mem_req %x.\n", req);
		return -EINVAL;
	}
	deb_v8("v8mem: %02x %02x %04x %04x, len: %d\n", request_type, req,
			wAddress, wIndex, buflen);

	len = usb_control_msg(fc_usb->udev, pipe,
			req,
			request_type,
			wAddress,
			wIndex,
			pbBuffer,
			buflen,
			nWaitTime * HZ);

	debug_dump(pbBuffer, len, deb_v8);
	return len == buflen ? 0 : -EIO;
}