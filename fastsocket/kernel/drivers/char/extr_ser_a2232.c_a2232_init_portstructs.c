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
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int close_delay; int closing_wait; int /*<<< orphan*/ * rd; int /*<<< orphan*/  magic; TYPE_2__ port; } ;
struct a2232_port {int which_a2232; int which_port_on_a2232; TYPE_1__ gs; scalar_t__ cd_status; scalar_t__ throttle_input; scalar_t__ disable_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2232_MAGIC ; 
 int HZ ; 
 int MAX_A2232_BOARDS ; 
 int NUMLINES ; 
 int /*<<< orphan*/  a2232_port_ops ; 
 struct a2232_port* a2232_ports ; 
 int /*<<< orphan*/  a2232_real_driver ; 
 int /*<<< orphan*/  tty_port_init (TYPE_2__*) ; 

__attribute__((used)) static void a2232_init_portstructs(void)
{
	struct a2232_port *port;
	int i;

	for (i = 0; i < MAX_A2232_BOARDS*NUMLINES; i++) {
		port = a2232_ports + i;
		tty_port_init(&port->gs.port);
		port->gs.port.ops = &a2232_port_ops;
		port->which_a2232 = i/NUMLINES;
		port->which_port_on_a2232 = i%NUMLINES;
		port->disable_rx = port->throttle_input = port->cd_status = 0;
		port->gs.magic = A2232_MAGIC;
		port->gs.close_delay = HZ/2;
		port->gs.closing_wait = 30 * HZ;
		port->gs.rd = &a2232_real_driver;
	}
}