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
typedef  int /*<<< orphan*/  u16 ;
struct usb_xpad {int pad_present; int /*<<< orphan*/  bulk_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpad360_process_packet (struct usb_xpad*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void xpad360w_process_packet(struct usb_xpad *xpad, u16 cmd, unsigned char *data)
{
	/* Presence change */
	if (data[0] & 0x08) {
		if (data[1] & 0x80) {
			xpad->pad_present = 1;
			usb_submit_urb(xpad->bulk_out, GFP_ATOMIC);
		} else
			xpad->pad_present = 0;
	}

	/* Valid pad data */
	if (!(data[1] & 0x1))
		return;

	xpad360_process_packet(xpad, cmd, &data[4]);
}