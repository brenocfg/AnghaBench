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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct qe_udc {int /*<<< orphan*/  usb_state; scalar_t__ device_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_STATE_ADDRESS ; 
 scalar_t__ ep0_prime_status (struct qe_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep0_stall (struct qe_udc*) ; 

__attribute__((used)) static void ch9setaddress(struct qe_udc *udc, u16 value, u16 index,
			u16 length)
{
	/* Save the new address to device struct */
	udc->device_address = (u8) value;
	/* Update usb state */
	udc->usb_state = USB_STATE_ADDRESS;

	/* Status phase , send a ZLP */
	if (ep0_prime_status(udc, USB_DIR_IN))
		qe_ep0_stall(udc);
}