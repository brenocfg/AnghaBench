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
struct usb_device {int dummy; } ;
struct swoc_info {void* LinuxVer; void* LinuxSKU; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWIMS_USB_REQUEST_GetSwocInfo ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  US_DEBUGP (char*) ; 
 void* le16_to_cpu (void*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sierra_get_swoc_info(struct usb_device *udev,
				struct swoc_info *swocInfo)
{
	int result;

	US_DEBUGP("SWIMS: Attempting to get TRU-Install info.\n");

	result = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			SWIMS_USB_REQUEST_GetSwocInfo,	/* __u8 request      */
			USB_TYPE_VENDOR | USB_DIR_IN,	/* __u8 request type */
			0,				/* __u16 value       */
			0,				/* __u16 index       */
			(void *) swocInfo,		/* void *data        */
			sizeof(struct swoc_info),	/* __u16 size 	     */
			USB_CTRL_SET_TIMEOUT);		/* int timeout 	     */

	swocInfo->LinuxSKU = le16_to_cpu(swocInfo->LinuxSKU);
	swocInfo->LinuxVer = le16_to_cpu(swocInfo->LinuxVer);
	return result;
}