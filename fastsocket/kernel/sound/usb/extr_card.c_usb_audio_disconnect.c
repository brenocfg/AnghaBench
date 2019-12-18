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
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  snd_usb_audio_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void usb_audio_disconnect(struct usb_interface *intf)
{
	snd_usb_audio_disconnect(interface_to_usbdev(intf),
				 usb_get_intfdata(intf));
}