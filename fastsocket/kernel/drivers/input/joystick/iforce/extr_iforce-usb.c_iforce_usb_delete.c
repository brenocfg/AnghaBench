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
struct iforce {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  out; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void iforce_usb_delete(struct iforce* iforce)
{
	usb_kill_urb(iforce->irq);
	usb_kill_urb(iforce->out);
	usb_kill_urb(iforce->ctrl);

	usb_free_urb(iforce->irq);
	usb_free_urb(iforce->out);
	usb_free_urb(iforce->ctrl);
}