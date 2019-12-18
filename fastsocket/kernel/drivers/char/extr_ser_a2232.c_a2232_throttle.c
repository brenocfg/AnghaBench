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
struct tty_struct {struct a2232_port* driver_data; } ;
struct a2232_port {int throttle_input; } ;

/* Variables and functions */

__attribute__((used)) static void a2232_throttle(struct tty_struct *tty)
{
/* Throttle: System cannot take another chars: Drop RTS or
             send the STOP char or whatever.
   The A2232 firmware does RTS/CTS anyway, and XON/XOFF
   if switched on. So the only thing we can do at this
   layer here is not taking any characters out of the
   A2232 buffer any more. */
	struct a2232_port *port = tty->driver_data;
	port->throttle_input = -1;
}