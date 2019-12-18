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
struct usb_hub {int /*<<< orphan*/  wakeup_bits; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct usb_hub* hdev_to_hub (struct usb_device*) ; 
 int /*<<< orphan*/  kick_khubd (struct usb_hub*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

void usb_wakeup_notification(struct usb_device *hdev,
		unsigned int portnum)
{
	struct usb_hub *hub;

	if (!hdev)
		return;

	hub = hdev_to_hub(hdev);
	if (hub) {
		set_bit(portnum, hub->wakeup_bits);
		kick_khubd(hub);
	}
}