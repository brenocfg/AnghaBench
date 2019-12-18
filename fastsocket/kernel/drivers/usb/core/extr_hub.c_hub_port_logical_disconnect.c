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
struct usb_hub {int /*<<< orphan*/  change_bits; int /*<<< orphan*/  intfdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hub_port_disable (struct usb_hub*,int,int) ; 
 int /*<<< orphan*/  kick_khubd (struct usb_hub*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hub_port_logical_disconnect(struct usb_hub *hub, int port1)
{
	dev_dbg(hub->intfdev, "logical disconnect on port %d\n", port1);
	hub_port_disable(hub, port1, 1);

	/* FIXME let caller ask to power down the port:
	 *  - some devices won't enumerate without a VBUS power cycle
	 *  - SRP saves power that way
	 *  - ... new call, TBD ...
	 * That's easy if this hub can switch power per-port, and
	 * khubd reactivates the port later (timer, SRP, etc).
	 * Powerdown must be optional, because of reset/DFU.
	 */

	set_bit(port1, hub->change_bits);
 	kick_khubd(hub);
}