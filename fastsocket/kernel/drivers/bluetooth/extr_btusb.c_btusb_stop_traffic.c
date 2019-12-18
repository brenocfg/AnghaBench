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
struct btusb_data {int /*<<< orphan*/  isoc_anchor; int /*<<< orphan*/  bulk_anchor; int /*<<< orphan*/  intr_anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btusb_stop_traffic(struct btusb_data *data)
{
	usb_kill_anchored_urbs(&data->intr_anchor);
	usb_kill_anchored_urbs(&data->bulk_anchor);
	usb_kill_anchored_urbs(&data->isoc_anchor);
}