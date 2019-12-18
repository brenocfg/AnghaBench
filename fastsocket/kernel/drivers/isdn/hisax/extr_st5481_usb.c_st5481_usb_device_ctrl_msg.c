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
typedef  int /*<<< orphan*/  u16 ;
struct st5481_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  ctrl_complete_t ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  usb_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void st5481_usb_device_ctrl_msg(struct st5481_adapter *adapter,
			 u8 request, u16 value,
			 ctrl_complete_t complete, void *context)
{
	usb_ctrl_msg(adapter, request, 
		     USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE, 
		     value, 0, complete, context);
}