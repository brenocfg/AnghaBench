#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct wahc {TYPE_3__* usb_iface; int /*<<< orphan*/  usb_dev; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_CLEAR_FEATURE ; 
 int /*<<< orphan*/  USB_REQ_SET_FEATURE ; 
 int USB_TYPE_CLASS ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __wa_feature(struct wahc *wa, unsigned op, u16 feature)
{
	return usb_control_msg(wa->usb_dev, usb_sndctrlpipe(wa->usb_dev, 0),
			op ? USB_REQ_SET_FEATURE : USB_REQ_CLEAR_FEATURE,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			feature,
			wa->usb_iface->cur_altsetting->desc.bInterfaceNumber,
			NULL, 0, 1000 /* FIXME: arbitrary */);
}