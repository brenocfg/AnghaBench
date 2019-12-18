#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long data; scalar_t__ expires; scalar_t__ function; } ;
struct nes_vnic {int /*<<< orphan*/  delayed_event; TYPE_2__ event_timer; int /*<<< orphan*/  last_dispatched_event; scalar_t__ logical_port; struct nes_device* nesdev; struct nes_ib_device* nesibdev; } ;
struct nes_ib_device {int /*<<< orphan*/  ibdev; } ;
struct nes_device {scalar_t__ iw_status; } ;
struct TYPE_4__ {scalar_t__ port_num; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 scalar_t__ NES_EVENT_DELAY ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 
 scalar_t__ nes_handle_delayed_event ; 

void  nes_port_ibevent(struct nes_vnic *nesvnic)
{
	struct nes_ib_device *nesibdev = nesvnic->nesibdev;
	struct nes_device *nesdev = nesvnic->nesdev;
	struct ib_event event;
	event.device = &nesibdev->ibdev;
	event.element.port_num = nesvnic->logical_port + 1;
	event.event = nesdev->iw_status ? IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;

	if (!nesvnic->event_timer.function) {
		ib_dispatch_event(&event);
		nesvnic->last_dispatched_event = event.event;
		nesvnic->event_timer.function = nes_handle_delayed_event;
		nesvnic->event_timer.data = (unsigned long) nesvnic;
		nesvnic->event_timer.expires = jiffies + NES_EVENT_DELAY;
		add_timer(&nesvnic->event_timer);
	} else {
		mod_timer(&nesvnic->event_timer, jiffies + NES_EVENT_DELAY);
	}
	nesvnic->delayed_event = event.event;
}