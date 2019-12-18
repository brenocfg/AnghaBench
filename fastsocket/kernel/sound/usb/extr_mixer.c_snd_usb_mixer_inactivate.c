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
struct usb_mixer_interface {int /*<<< orphan*/  rc_urb; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void snd_usb_mixer_inactivate(struct usb_mixer_interface *mixer)
{
	usb_kill_urb(mixer->urb);
	usb_kill_urb(mixer->rc_urb);
}