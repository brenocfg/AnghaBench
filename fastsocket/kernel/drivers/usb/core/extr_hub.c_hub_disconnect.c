#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_hub {int disconnected; int /*<<< orphan*/  kref; int /*<<< orphan*/  buffer; int /*<<< orphan*/  status; int /*<<< orphan*/  descriptor; int /*<<< orphan*/  port_owners; int /*<<< orphan*/  urb; TYPE_1__* hdev; scalar_t__ error; int /*<<< orphan*/  event_list; } ;
struct TYPE_2__ {scalar_t__ speed; scalar_t__ maxchild; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUB_DISCONNECT ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  highspeed_hubs ; 
 int /*<<< orphan*/  hub_event_lock ; 
 int /*<<< orphan*/  hub_quiesce (struct usb_hub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_release ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hub_disconnect(struct usb_interface *intf)
{
	struct usb_hub *hub = usb_get_intfdata (intf);

	/* Take the hub off the event list and don't let it be added again */
	spin_lock_irq(&hub_event_lock);
	list_del_init(&hub->event_list);
	hub->disconnected = 1;
	spin_unlock_irq(&hub_event_lock);

	/* Disconnect all children and quiesce the hub */
	hub->error = 0;
	hub_quiesce(hub, HUB_DISCONNECT);

	usb_set_intfdata (intf, NULL);
	hub->hdev->maxchild = 0;

	if (hub->hdev->speed == USB_SPEED_HIGH)
		highspeed_hubs--;

	usb_free_urb(hub->urb);
	kfree(hub->port_owners);
	kfree(hub->descriptor);
	kfree(hub->status);
	kfree(hub->buffer);

	kref_put(&hub->kref, hub_release);
}