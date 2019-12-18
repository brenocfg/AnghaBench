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
struct tty_struct {int index; struct a2232_port* driver_data; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flags; struct tty_struct* tty; } ;
struct TYPE_4__ {TYPE_1__ port; } ;
struct a2232_port {TYPE_2__ gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_ACTIVE ; 
 int /*<<< orphan*/  a2232_enable_rx_interrupts (struct a2232_port*) ; 
 struct a2232_port* a2232_ports ; 
 int gs_block_til_ready (struct a2232_port*,struct file*) ; 
 int gs_init_port (TYPE_2__*) ; 

__attribute__((used)) static int  a2232_open(struct tty_struct * tty, struct file * filp)
{
/* More or less stolen from other drivers. */
	int line;
	int retval;
	struct a2232_port *port;

	line = tty->index;
	port = &a2232_ports[line];
	
	tty->driver_data = port;
	port->gs.port.tty = tty;
	port->gs.port.count++;
	retval = gs_init_port(&port->gs);
	if (retval) {
		port->gs.port.count--;
		return retval;
	}
	port->gs.port.flags |= GS_ACTIVE;
	retval = gs_block_til_ready(port, filp);

	if (retval) {
		port->gs.port.count--;
		return retval;
	}

	a2232_enable_rx_interrupts(port);
	
	return 0;
}