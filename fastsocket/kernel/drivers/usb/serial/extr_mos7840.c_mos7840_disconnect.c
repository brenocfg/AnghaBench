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
struct usb_serial {int num_ports; int /*<<< orphan*/ * port; } ;
struct moschip_port {int zombie; int /*<<< orphan*/  control_urb; int /*<<< orphan*/  pool_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,...) ; 
 struct moschip_port* mos7840_get_port_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mos7840_disconnect(struct usb_serial *serial)
{
	int i;
	unsigned long flags;
	struct moschip_port *mos7840_port;
	dbg("%s", " disconnect :entering..........");

	if (!serial) {
		dbg("%s", "Invalid Handler");
		return;
	}

	/* check for the ports to be closed,close the ports and disconnect */

	/* free private structure allocated for serial port  *
	 * stop reads and writes on all ports                */

	for (i = 0; i < serial->num_ports; ++i) {
		mos7840_port = mos7840_get_port_private(serial->port[i]);
		dbg ("mos7840_port %d = %p", i, mos7840_port);
		if (mos7840_port) {
			spin_lock_irqsave(&mos7840_port->pool_lock, flags);
			mos7840_port->zombie = 1;
			spin_unlock_irqrestore(&mos7840_port->pool_lock, flags);
			usb_kill_urb(mos7840_port->control_urb);
		}
	}

	dbg("%s", "Thank u :: ");

}