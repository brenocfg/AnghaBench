#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct pegasus {int /*<<< orphan*/  carrier_check; TYPE_2__* intr_urb; TYPE_1__* rx_urb; int /*<<< orphan*/  net; } ;
struct TYPE_4__ {scalar_t__ actual_length; scalar_t__ status; } ;
struct TYPE_3__ {scalar_t__ actual_length; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARRIER_CHECK_DELAY ; 
 int /*<<< orphan*/  intr_callback (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pegasus_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_bulk_callback (TYPE_1__*) ; 
 struct pegasus* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int pegasus_resume (struct usb_interface *intf)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	netif_device_attach (pegasus->net);
	if (netif_running(pegasus->net)) {
		pegasus->rx_urb->status = 0;
		pegasus->rx_urb->actual_length = 0;
		read_bulk_callback(pegasus->rx_urb);

		pegasus->intr_urb->status = 0;
		pegasus->intr_urb->actual_length = 0;
		intr_callback(pegasus->intr_urb);
	}
	queue_delayed_work(pegasus_workqueue, &pegasus->carrier_check,
				CARRIER_CHECK_DELAY);
	return 0;
}