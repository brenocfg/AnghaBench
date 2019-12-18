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
struct tty_struct {TYPE_1__* termios; scalar_t__ driver_data; } ;
struct Port {int /*<<< orphan*/  State; } ;
struct TYPE_2__ {int c_cflag; } ;

/* Variables and functions */
 int CRTSCTS ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  RIO_THROTTLE_RX ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 

__attribute__((used)) static void rio_throttle(struct tty_struct *tty)
{
	struct Port *port = (struct Port *) tty->driver_data;

	func_enter();
	/* If the port is using any type of input flow
	 * control then throttle the port.
	 */

	if ((tty->termios->c_cflag & CRTSCTS) || (I_IXOFF(tty))) {
		port->State |= RIO_THROTTLE_RX;
	}

	func_exit();
}