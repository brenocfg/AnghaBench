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
struct urb {struct sisusb_usb_data* context; } ;
struct sisusb_usb_data {int completein; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  present; int /*<<< orphan*/  sisusb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sisusb_bulk_completein(struct urb *urb)
{
	struct sisusb_usb_data *sisusb = urb->context;

	if (!sisusb || !sisusb->sisusb_dev || !sisusb->present)
		return;

	sisusb->completein = 1;
	wake_up(&sisusb->wait_q);
}