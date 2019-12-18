#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* termios; struct sx_port* driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__ port; } ;
struct sx_port {TYPE_3__ gs; } ;
struct TYPE_4__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  SX_RX_THROTTLE ; 
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 

__attribute__((used)) static void sx_throttle(struct tty_struct *tty)
{
	struct sx_port *port = tty->driver_data;

	func_enter2();
	/* If the port is using any type of input flow
	 * control then throttle the port.
	 */
	if ((tty->termios->c_cflag & CRTSCTS) || (I_IXOFF(tty))) {
		port->gs.port.flags |= SX_RX_THROTTLE;
	}
	func_exit();
}