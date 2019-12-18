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
struct moschip_port {struct moschip_port* dr; struct moschip_port* ctrl_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  kfree (struct moschip_port*) ; 
 struct moschip_port* mos7840_get_port_private (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mos7840_release(struct usb_serial *serial)
{
	int i;
	struct moschip_port *mos7840_port;
	dbg("%s", " release :entering..........");

	if (!serial) {
		dbg("%s", "Invalid Handler");
		return;
	}

	/* check for the ports to be closed,close the ports and disconnect */

	/* free private structure allocated for serial port  *
	 * stop reads and writes on all ports                */

	for (i = 0; i < serial->num_ports; ++i) {
		mos7840_port = mos7840_get_port_private(serial->port[i]);
		dbg("mos7840_port %d = %p", i, mos7840_port);
		if (mos7840_port) {
			kfree(mos7840_port->ctrl_buf);
			kfree(mos7840_port->dr);
			kfree(mos7840_port);
		}
	}

	dbg("%s", "Thank u :: ");

}