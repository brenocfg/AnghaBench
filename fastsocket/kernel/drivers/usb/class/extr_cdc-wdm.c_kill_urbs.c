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
struct wdm_device {int /*<<< orphan*/  response; int /*<<< orphan*/  validity; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kill_urbs(struct wdm_device *desc)
{
	/* the order here is essential */
	usb_kill_urb(desc->command);
	usb_kill_urb(desc->validity);
	usb_kill_urb(desc->response);
}