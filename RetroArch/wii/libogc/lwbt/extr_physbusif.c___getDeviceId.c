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
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_OH0_DEVICE_ID ; 
 int /*<<< orphan*/  USB_OH1_DEVICE_ID ; 
 scalar_t__ USB_OpenDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __ntd_ohci ; 
 int __ntd_ohci_initflag ; 
 int /*<<< orphan*/  __ntd_usb_fd ; 
 TYPE_1__ __usbdev ; 

__attribute__((used)) static s32 __getDeviceId(u16 vid,u16 pid)
{
	s32 ret = 0;

	if(__ntd_ohci_initflag==0x0001) {
		if(__ntd_ohci==0x0000)
			ret = USB_OpenDevice(USB_OH0_DEVICE_ID,vid,pid,&__usbdev.fd);
		else if(__ntd_ohci==0x0001)
			ret = USB_OpenDevice(USB_OH1_DEVICE_ID,vid,pid,&__usbdev.fd);
	} else
		ret = USB_OpenDevice(USB_OH1_DEVICE_ID,vid,pid,&__usbdev.fd);

	//printf("__getDeviceId(%04x,%04x,%d)\n",vid,pid,__usbdev.fd);
	if(ret==0) __ntd_usb_fd = __usbdev.fd;
	return ret;
}