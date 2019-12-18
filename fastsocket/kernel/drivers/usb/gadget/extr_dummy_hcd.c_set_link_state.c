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
struct dummy {int active; int port_status; int old_status; scalar_t__ rh_state; int old_active; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; scalar_t__ resuming; scalar_t__ udc_suspended; int /*<<< orphan*/  pullup; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* suspend ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ DUMMY_RH_SUSPENDED ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int USB_PORT_STAT_POWER ; 
 int USB_PORT_STAT_RESET ; 
 int USB_PORT_STAT_SUSPEND ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_activity (struct dummy*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_link_state (struct dummy *dum)
{
	dum->active = 0;
	if ((dum->port_status & USB_PORT_STAT_POWER) == 0)
		dum->port_status = 0;

	/* UDC suspend must cause a disconnect */
	else if (!dum->pullup || dum->udc_suspended) {
		dum->port_status &= ~(USB_PORT_STAT_CONNECTION |
					USB_PORT_STAT_ENABLE |
					USB_PORT_STAT_LOW_SPEED |
					USB_PORT_STAT_HIGH_SPEED |
					USB_PORT_STAT_SUSPEND);
		if ((dum->old_status & USB_PORT_STAT_CONNECTION) != 0)
			dum->port_status |= (USB_PORT_STAT_C_CONNECTION << 16);
	} else {
		dum->port_status |= USB_PORT_STAT_CONNECTION;
		if ((dum->old_status & USB_PORT_STAT_CONNECTION) == 0)
			dum->port_status |= (USB_PORT_STAT_C_CONNECTION << 16);
		if ((dum->port_status & USB_PORT_STAT_ENABLE) == 0)
			dum->port_status &= ~USB_PORT_STAT_SUSPEND;
		else if ((dum->port_status & USB_PORT_STAT_SUSPEND) == 0 &&
				dum->rh_state != DUMMY_RH_SUSPENDED)
			dum->active = 1;
	}

	if ((dum->port_status & USB_PORT_STAT_ENABLE) == 0 || dum->active)
		dum->resuming = 0;

	if ((dum->port_status & USB_PORT_STAT_CONNECTION) == 0 ||
			(dum->port_status & USB_PORT_STAT_RESET) != 0) {
		if ((dum->old_status & USB_PORT_STAT_CONNECTION) != 0 &&
				(dum->old_status & USB_PORT_STAT_RESET) == 0 &&
				dum->driver) {
			stop_activity (dum);
			spin_unlock (&dum->lock);
			dum->driver->disconnect (&dum->gadget);
			spin_lock (&dum->lock);
		}
	} else if (dum->active != dum->old_active) {
		if (dum->old_active && dum->driver->suspend) {
			spin_unlock (&dum->lock);
			dum->driver->suspend (&dum->gadget);
			spin_lock (&dum->lock);
		} else if (!dum->old_active && dum->driver->resume) {
			spin_unlock (&dum->lock);
			dum->driver->resume (&dum->gadget);
			spin_lock (&dum->lock);
		}
	}

	dum->old_status = dum->port_status;
	dum->old_active = dum->active;
}