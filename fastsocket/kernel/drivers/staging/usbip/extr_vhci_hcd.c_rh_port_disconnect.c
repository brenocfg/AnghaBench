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
struct TYPE_2__ {int* port_status; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int USB_PORT_FEAT_C_CONNECTION ; 
 int USB_PORT_STAT_CONNECTION ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* the_controller ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rh (char*,int) ; 

void rh_port_disconnect(int rhport)
{
	unsigned long flags;

	usbip_dbg_vhci_rh("rh_port_disconnect %d\n", rhport);

	spin_lock_irqsave(&the_controller->lock, flags);
	/* stop_activity(dum, driver); */
	the_controller->port_status[rhport] &= ~USB_PORT_STAT_CONNECTION;
	the_controller->port_status[rhport] |=
					(1 << USB_PORT_FEAT_C_CONNECTION);


	/* not yet complete the disconnection
	 * spin_lock(&vdev->ud.lock);
	 * vdev->ud.status = VHC_ST_DISCONNECT;
	 * spin_unlock(&vdev->ud.lock); */

	spin_unlock_irqrestore(&the_controller->lock, flags);
}